#ifndef QXTMDNS_H
#define QXTMDNS_H

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-qt4/qt-watch.h>

// This is basically a struct of data with functions in it for organization :P
class QxtMDNS : public QObject
{
	Q_OBJECT
public:
	QxtMDNS(int id = -1, QObject* parent = 0);

	void doLookup(QString name, QObject * receiver, const char * member);
	void cancelLookup();
	
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
