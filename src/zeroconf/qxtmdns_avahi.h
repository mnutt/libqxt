#ifndef QXTMDNS_H
#define QXTMDNS_H

#include "qxtglobal.h"
#include <QObject>
#include <QxtPimpl>

class QxtMDNSPrivate;

// This class just throws QHostInfo objects at the receiver...
// The receiver slot should take 1 parameter, a QHostInfo...
class QXT_ZEROCONF_EXPORT QxtMDNS : public QObject
{
	QXT_DECLARE_PRIVATE(QxtMDNS);
	Q_OBJECT
public:
	QxtMDNS(int id = -1, QObject* parent = 0);

	void doLookup(QString name, QObject * receiver, const char * member);
	void cancelLookup();
};

#endif //#ifndef QXTMDNS_H
