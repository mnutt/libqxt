#ifndef FOO_H
#define FOO_H

#include <qxtglobal.h>
#include <QObject>
#include <QFlags>
#include <QStringList>
#include <QAbstractSocket>
#include <qxtdiscoverableservicename.h>
#include <qxtdiscoverableservice.h>
#include <qxtservicebrowser.h>

class Foo : public QObject {
Q_OBJECT
public:
    QxtServiceBrowser* browser;
public slots:
    void err(int err) {
        qDebug() << "error=" << err;
    }
    void ok() {
        qDebug() << "registered yay";
    }
    void add(const QString& name, const QString& domain) {
        qDebug() << "added" << name;
        QString st = "_"+browser->serviceType()+"._";
        if(browser->socketType() == QAbstractSocket::TcpSocket) {
            st += "tcp";
        } else {
            st += "udp";
        }
        QxtDiscoverableService* svc = new QxtDiscoverableService(st, name, browser);
        svc->setDomain(domain);
        QObject::connect(svc, SIGNAL(resolved(QByteArray)), this, SLOT(resolved(QByteArray)));
        QObject::connect(svc, SIGNAL(resolveError(int)), this, SLOT(err(int)));
        svc->resolve();
    }
    void remove(const QString& name) {
        qDebug() << "removed" << name;
    }
    void resolved(const QByteArray& domainName) {
        QxtDiscoverableService* svc = static_cast<QxtDiscoverableService*>(sender());
        qDebug() << "resolved " << domainName << " on port " << svc->port();
    }
};

#endif
