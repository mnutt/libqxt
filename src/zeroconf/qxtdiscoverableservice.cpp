#include "qxtdiscoverableservice.h"
#include "qxtdiscoverableservice_p.h"
#include <QSocketNotifier>
#include <QList>
#include <QPair>
#include <QtDebug>

void QxtDiscoverableServicePrivate::registerServiceCallback(DNSServiceRef service, DNSServiceFlags flags,
        DNSServiceErrorType errCode, const char* name, const char* regtype, const char* domain, void* context)
{
    Q_UNUSED(service);
    Q_UNUSED(flags);
    Q_UNUSED(regtype);
    QxtDiscoverableServicePrivate* self = reinterpret_cast<QxtDiscoverableServicePrivate*>(context);
    QxtDiscoverableService* pub = &(self->qxt_p());
    if(errCode == kDNSServiceErr_NoError) {
        pub->setServiceName(name);
        pub->setDomain(domain);
        self->state = QxtDiscoverableService::Registered;
        emit self->qxt_p().registered();
    } else {
        self->state = QxtDiscoverableService::Unknown;
        emit self->qxt_p().registrationError((QxtDiscoverableService::ErrorCode)errCode);
    }
}

void QxtDiscoverableServicePrivate::resolveServiceCallback(DNSServiceRef service, DNSServiceFlags flags, quint32 iface,
        DNSServiceErrorType errCode, const char* fullname, const char* host, quint16 port, quint16 txtLen,
        const unsigned char* txt, void* context)
{
    Q_UNUSED(service);
    Q_UNUSED(host);
    Q_UNUSED(txtLen);
    Q_UNUSED(txt);
    Q_UNUSED(flags);
    QxtDiscoverableServicePrivate* self = reinterpret_cast<QxtDiscoverableServicePrivate*>(context);
    if(errCode == kDNSServiceErr_NoError) {
        //QxtDiscoverableServiceName name(fullname);
        //self->name = name;
        //self->domain = domain;
        self->port = port;
        self->iface = iface;
        emit self->qxt_p().resolved(fullname);
    } else {
        self->state = QxtDiscoverableService::Unknown;
        emit self->qxt_p().resolveError((QxtDiscoverableService::ErrorCode)errCode);
    }
}

void QxtDiscoverableServicePrivate::socketData()
{
    DNSServiceProcessResult(service);
}

QxtDiscoverableService::QxtDiscoverableService(const QString& serviceType, QObject* parent)
: QObject(parent), QxtDiscoverableServiceName(QString(), serviceType, QString())
{
    QXT_INIT_PRIVATE(QxtDiscoverableService);
    qxt_zeroconf_parse_subtypes(&qxt_d(), serviceType.toUtf8());
}

QxtDiscoverableService::QxtDiscoverableService(const QString& serviceType, const QString& serviceName, QObject* parent)
: QObject(parent), QxtDiscoverableServiceName(serviceName, serviceType, QString())
{
    QXT_INIT_PRIVATE(QxtDiscoverableService);
    qxt_zeroconf_parse_subtypes(&qxt_d(), serviceType.toUtf8());
}

QxtDiscoverableService::~QxtDiscoverableService()
{
    if(state() == Registered || state() == Resolved)
        releaseService();
}

QxtDiscoverableService::State QxtDiscoverableService::state() const {
    return qxt_d().state;
}

QStringList QxtDiscoverableService::serviceSubTypes() const
{
    return qxt_d().serviceSubTypes;
}

void QxtDiscoverableService::setServiceSubTypes(const QStringList& subtypes)
{
    if(state() != Unknown)
        qWarning() << "QxtDiscoverableService: Setting service subtypes while not in Unknown state has no effect";
    qxt_d().serviceSubTypes = subtypes;
}

void QxtDiscoverableService::addServiceSubType(const QString& subtype)
{
    if(state() != Unknown)
        qWarning() << "QxtDiscoverableService: Setting service subtypes while not in Unknown state has no effect";
    qxt_d().serviceSubTypes << subtype;
}

void QxtDiscoverableService::removeServiceSubType(const QString& subtype)
{
    if(state() != Unknown)
        qWarning() << "QxtDiscoverableService: Setting service subtypes while not in Unknown state has no effect";
    qxt_d().serviceSubTypes.removeAll(subtype);
}

bool QxtDiscoverableService::hasServiceSubType(const QString& subtype)
{
    return qxt_d().serviceSubTypes.contains(subtype);
}

quint16 QxtDiscoverableService::port() const
{
    return ntohs(qxt_d().port);
}

void QxtDiscoverableService::setPort(quint16 port)
{
    qxt_d().port = htons(port);
}

void QxtDiscoverableService::registerService(bool noAutoRename)
{
    if(state() != Unknown) {
        qWarning() << "QxtDiscoverableService: Cannot register service while not in Unknown state";
        emit registrationError(0);
        return;
    }

    QStringList subtypes = qxt_d().serviceSubTypes;
    subtypes.prepend(fullServiceType());

    DNSServiceErrorType err;
    err = DNSServiceRegister(&(qxt_d().service),
                             noAutoRename ? kDNSServiceFlagsNoAutoRename : 0,
                             qxt_d().iface,
                             serviceName().isEmpty() ? 0 : serviceName().toUtf8().constData(),
                             subtypes.join(",_").toUtf8().constData(),
                             domain().isEmpty() ? 0 : domain().toUtf8().constData(),
                             host().isEmpty() ? 0 : host().toUtf8().constData(),
                             qxt_d().port,
                             1, // must include null terminator
                             "",
                             QxtDiscoverableServicePrivate::registerServiceCallback,
                             &qxt_d());
    if(err != kDNSServiceErr_NoError) {
        qxt_d().state = Unknown;
        emit registrationError(err);
    } else {
        qxt_d().state = Registering;
        qxt_d().notifier = new QSocketNotifier(DNSServiceRefSockFD(qxt_d().service), QSocketNotifier::Read, this);
        QObject::connect(qxt_d().notifier, SIGNAL(activated(int)), &qxt_d(), SLOT(socketData()));
    }
}

void QxtDiscoverableService::resolve(bool forceMulticast)
{
    if(state() != Unknown && state() != Found) {
        qWarning() << "QxtDiscoverableService: Cannot resolve service while not in Unknown or Found state";
        emit resolveError(0);
        return;
    }

    DNSServiceErrorType err;
    err = DNSServiceResolve(&(qxt_d().service),
                            (forceMulticast ? kDNSServiceFlagsForceMulticast : 0),
                            qxt_d().iface,
                            serviceName().toUtf8().constData(),
                            fullServiceType().constData(),
                            domain().toUtf8().constData(),
                            QxtDiscoverableServicePrivate::resolveServiceCallback,
                            &qxt_d());
    if(err != kDNSServiceErr_NoError) {
        qxt_d().state = Unknown;
        emit resolveError(err);
    } else {
        qxt_d().state = Resolving;
        qxt_d().notifier = new QSocketNotifier(DNSServiceRefSockFD(qxt_d().service), QSocketNotifier::Read, this);
        QObject::connect(qxt_d().notifier, SIGNAL(activated(int)), &qxt_d(), SLOT(socketData()));
    }
}

void QxtDiscoverableService::releaseService()
{
    if(state() != Registered && state() != Resolved) {
        qWarning() << "QxtDiscoverableService: Attempting to unregister an unresolved, unregistered service";
    } else {
        DNSServiceRefDeallocate(qxt_d().service);
        qxt_d().notifier->deleteLater();
    }
}

