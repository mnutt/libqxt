#include "qxtmdnslookup.h"
#include "qxtmdnslookup_p.h"
#include <qxtmetaobject.h>
#include <QDebug>

QxtMDNSLookup::QxtMDNSLookup()
{
	QXT_INIT_PRIVATE(QxtMDNSLookup);
}

QxtMDNSLookup::~QxtMDNSLookup()
{
}

void QxtMDNSLookup::lookupHost(QString name, QObject * receiver, const char * member)
{
	QxtMDNSLookupWorker* md = new QxtMDNSLookupWorker(receiver);
	md->doLookup(name, receiver, member);
}


/****** QxtMDNSLookupWorker ******/

QxtMDNSLookupWorker::QxtMDNSLookupWorker(QObject* parent)
		: QObject(parent)
{
}
