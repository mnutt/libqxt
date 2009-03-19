#include "foo.h"
#include <qxtdiscoverableservice.h>
#include <qxtservicebrowser.h>
#include <QxtSignalWaiter>
#include <QCoreApplication>
#include <QtDebug>

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    QxtDiscoverableService svc("daap");
    svc.setPort(9123);
    Foo foo;
    QObject::connect(&svc, SIGNAL(registered()), &foo, SLOT(ok()));
    QObject::connect(&svc, SIGNAL(registrationError(int)), &foo, SLOT(err(int)));
    qDebug() << "registering...";
    svc.registerService(true);
    qDebug() << "registerService invoked";

    QxtServiceBrowser browser("daap");
    foo.browser = &browser;
    QObject::connect(&browser, SIGNAL(browsingFailed(int)), &foo, SLOT(err(int)));
    QObject::connect(&browser, SIGNAL(serviceAdded(QString,QString)), &foo, SLOT(add(QString,QString)));
    QObject::connect(&browser, SIGNAL(serviceRemoved(QString,QString)), &foo, SLOT(remove(QString)));
    browser.browse();

    app.exec();
}
