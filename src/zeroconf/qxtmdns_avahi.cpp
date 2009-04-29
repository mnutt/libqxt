#include "qxtmdns_avahi.h"
#include <qxtmetaobject.h>
#include <QDebug>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <avahi-common/error.h>
#include <arpa/inet.h>

QxtMDNS::QxtMDNS(int id, QObject* parent)
		: QObject(parent),
		info(id),
		client(NULL),
		recordbrowser(NULL),
		sent(false)
{
}

void QxtMDNS::doLookup(QString n, QObject * r, const char * m)
{
	name = n;
	receiver = r;
	member = QxtMetaObject::methodName(m);
	int error;
	client = avahi_client_new(
	             avahi_qt_poll_get(), // use the qt event loop
	             (AvahiClientFlags)0,
	             QxtMDNS::avahiClientCallback,
	             this,
	             &error
	         );
}

void QxtMDNS::avahiClientCallback(AvahiClient *s, AvahiClientState state, void *userdata)
{
	QxtMDNS* md = static_cast<QxtMDNS*>(userdata);
	md->client = s;
	if (state == AVAHI_CLIENT_S_RUNNING)
	{
		md->recordbrowser = avahi_record_browser_new(
		                        s,
		                        AVAHI_IF_UNSPEC,
		                        AVAHI_PROTO_INET,
		                        md->name.toAscii().constData(),
		                        AVAHI_DNS_CLASS_IN,
		                        AVAHI_DNS_TYPE_A,
		                        (AvahiLookupFlags)0,
		                        QxtMDNS::avahiRecordBrowserCallback,
		                        md);
		if(md->recordbrowser == NULL)
		{
			md->info.setError(QHostInfo::UnknownError);
			md->info.setErrorString(avahi_strerror(avahi_client_errno(md->client)));
			QMetaObject::invokeMethod(md->receiver, md->member, Q_ARG(QHostInfo, md->info));
			md->sent = true;
			md->cancelLookup();
		}
	}
}

void QxtMDNS::avahiRecordBrowserCallback(AvahiRecordBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, const char *name, uint16_t clazz, uint16_t type, const void *rdata, size_t size, AvahiLookupResultFlags flags, void *userdata)
{
	///@TODO Support IPv6
	Q_UNUSED(interface);
	Q_UNUSED(protocol);
	Q_UNUSED(name);
	Q_UNUSED(clazz);
	Q_UNUSED(type);
	Q_UNUSED(size);
	Q_UNUSED(flags);
	QxtMDNS* md = static_cast<QxtMDNS*>(userdata);
	md->recordbrowser = b;
// 	qDebug() << "Return thing" << md->name << name << size;
	switch (event)
	{
		case AVAHI_BROWSER_NEW:
		{
			//Found an entry!
			uint32_t ip = htonl(*static_cast<const uint32_t*>(rdata));
			if (md->sent)
			{
				QHostInfo info(md->info.lookupId());
				info.setAddresses(QList<QHostAddress>() << QHostAddress(ip));
				QMetaObject::invokeMethod(md->receiver, md->member, Q_ARG(QHostInfo, info));
			}
			else
			{
				md->addresses << QHostAddress(ip);
			}
			break;
		}
		case AVAHI_BROWSER_REMOVE:
		{
			uint32_t ip = htonl(*static_cast<const uint32_t*>(rdata));
			md->addresses.removeAll(QHostAddress(ip));
			break;
		}
		case AVAHI_BROWSER_CACHE_EXHAUSTED:
			break;
		case AVAHI_BROWSER_ALL_FOR_NOW:
			if (md->addresses.count() == 0)
			{
				md->info.setError(QHostInfo::HostNotFound);
				md->info.setErrorString("The host was not found.");
			}
			else
			{
				md->info.setAddresses(md->addresses);
				md->addresses.clear();
			}
			QMetaObject::invokeMethod(md->receiver, md->member, Q_ARG(QHostInfo, md->info));
			md->sent = true;
			break;
		case AVAHI_BROWSER_FAILURE:

			if (md->sent)
			{
				QHostInfo info(md->info.lookupId());
				info.setError(QHostInfo::UnknownError);
				info.setErrorString(avahi_strerror(avahi_client_errno(md->client)));
				info.setAddresses(md->addresses);
				QMetaObject::invokeMethod(md->receiver, md->member, Q_ARG(QHostInfo, info));
			}
			else
			{
				md->info.setError(QHostInfo::UnknownError);
				md->info.setErrorString(avahi_strerror(avahi_client_errno(md->client)));
				md->info.setAddresses(md->addresses);
				md->addresses.clear();
				QMetaObject::invokeMethod(md->receiver, md->member, Q_ARG(QHostInfo, md->info));
				md->sent = true;
			}
			break;
	}
}

void QxtMDNS::cancelLookup()
{
	if (recordbrowser != NULL)
		avahi_record_browser_free(recordbrowser);

	if (client != NULL)
		avahi_client_free(client);

	deleteLater();
}

