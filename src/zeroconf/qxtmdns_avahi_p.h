#ifndef QXTMDNS_P_H
#define QXTMDNS_P_H

#include "qxtmdns_avahi.h"
#include <QHostAddress>
#include <QHostInfo>
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <qxtavahipoll.h>

class QxtMDNSPrivate : public QxtPrivate<QxtMDNS>
{
public:
	QxtMDNSPrivate()
	{
	}

	static void avahiClientCallback(AvahiClient *s, AvahiClientState state, void *userdata);
	static void avahiRecordBrowserCallback(AvahiRecordBrowser *b, AvahiIfIndex interface, AvahiProtocol protocol, AvahiBrowserEvent event, const char *name, uint16_t clazz, uint16_t type, const void *rdata, size_t size, AvahiLookupResultFlags flags, void *userdata);

	QHostInfo info;
	QList<QHostAddress> addresses;

	QString name;
	QObject* receiver;
	QByteArray member;
	AvahiClient* client;
	AvahiRecordBrowser* recordbrowser;
	bool sent;
	int id;
};


#endif //#ifndef QXTMDNS_H
