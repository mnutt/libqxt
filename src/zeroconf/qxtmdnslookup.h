#ifndef QXTMDNSLOOKUP_H
#define QXTMDNSLOOKUP_H

#include <qxtglobal.h>
#include <qxtpimpl.h>

class QxtMDNSLookupPrivate;
class QObject;

class QxtMDNSLookup
{
QXT_DECLARE_PRIVATE(QxtMDNSLookup);
public:
	QxtMDNSLookup();
	~QxtMDNSLookup();
	
	static void lookupHost(QString name, QObject * receiver, const char * member);
	
};





#endif //#ifndef QXTMDNSLOOKUP_H
