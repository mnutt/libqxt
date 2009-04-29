#ifndef QXTMDNSLOOKUP_P_H
#define QXTMDNSLOOKUP_P_H

#include <qxtglobal.h>

#include <QObject>
#include <QSocketNotifier>
#include <qxtmdnslookup.h>

#define QXT_USE_AVAHI

#ifdef QXT_USE_AVAHI
#include <avahi-client/lookup.h>
#include <avahi-qt4/qt-watch.h>
#else
#include <dns_sd.h>
#endif

class QxtMDNSLookupPrivate : public QxtPrivate<QxtMDNSLookup>
{
public:
	QxtMDNSLookupPrivate()
	{
	}
	QXT_DECLARE_PUBLIC(QxtMDNSLookup);

};

class QxtMDNSLookupWorker : public QObject
{
	Q_OBJECT
public:
	QxtMDNSLookupWorker(QObject* parent = 0);
	QSocketNotifier* notifier;

	QString _name;
	QObject* _receiver;
	const char* _member;
	void doLookup(QString name, QObject * receiver, const char * member);

#ifdef QXT_USE_AVAHI
	AvahiClient* client;
	AvahiHostNameResolver* ref;
	static void avahiClientCallback(AvahiClient *s, AvahiClientState state, void *userdata);
	void doResolve();
#else
	DNSServiceRef* ref;
	static void DNSServiceQueryRecordCallback(DNSServiceRef DNSServiceRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char *fullname, uint16_t rrtype, uint16_t rrclass, uint16_t rdlen, const void *rdata, uint32_t ttl, void *context);
public Q_SLOTS:
	void socketData();
#endif


};




#endif //#ifndef QXTMDNSLOOKUP_P_H
