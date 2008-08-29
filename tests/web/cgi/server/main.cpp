#include <QCoreApplication>
#include <qxtwebcgiservice.h>
#include <QxtHttpSessionManager>
#include <QtDebug>

#ifdef Q_OS_WIN
#   define CLIENT_NAME "\\cgiclient.exe"
#else
#   define CLIENT_NAME "/cgiclient"
#endif

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    QxtHttpSessionManager m;
    m.setConnector(QxtHttpSessionManager::HttpServer);
    QxtWebCgiService* svc = new QxtWebCgiService(app.applicationDirPath() + CLIENT_NAME, &m, &m);
    qDebug() << svc->binary();
    m.setStaticContentService(svc);
    m.setAutoCreateSession(false);
    m.setPort(8192);
    m.start();
    return app.exec();
}
