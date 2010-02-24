#include <QCoreApplication>

#include <QxtHttpServerConnector>
#include <QxtHttpSessionManager>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>


class MyService : public QxtWebSlotService{
    Q_OBJECT;
public:
    MyService(QxtAbstractWebSessionManager * sm, QObject * parent = 0 ): QxtWebSlotService(sm,parent){
    }
public slots:
    void index(QxtWebRequestEvent* event)
    {
        postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, "<h1>It Works!</h1>"));
    }
};


int main(int argc, char ** argv){

        QCoreApplication app(argc,argv);

        QxtHttpServerConnector connector;

        QxtHttpSessionManager session;
        session.setPort(8080);
        session.setConnector(&connector);

        MyService s1(&session);
        session.setStaticContentService ( &s1);

        session.start();
        return app.exec();
}

#include "main.moc"
