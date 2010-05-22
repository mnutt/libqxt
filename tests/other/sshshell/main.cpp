#include <QCoreApplication>
#include <QxtSshClient>
#include <QxtSshProcess>

#include <QDebug>
#include <QxtStdio>
#include <QUrl>
#include <QDir>
#include <QStringList>

#ifdef Q_OS_UNIX
#include <termios.h>
#endif

class QxtSshTest: public QObject{
    Q_OBJECT
public:
    QxtSshTest(){
        QUrl u=QUrl::fromUserInput(qApp->arguments().at(1));
        connect(&client,SIGNAL(connected()),this,SLOT(connected()));
        connect(&client,SIGNAL(authenticationRequired(QList<QxtSshClient::AuthenticationMethod>)),
                this,SLOT(authenticationRequired(QList<QxtSshClient::AuthenticationMethod>)));
        connect(&client,SIGNAL(error (QxtSshClient::Error)),this,SLOT(error (QxtSshClient::Error)));
        client.loadKnownHosts(QDir::homePath ()+"/.ssh/known_hosts");
        client.connectToHost(u.userName(),u.host());
        client.setKeyFiles(QDir::homePath ()+"/.ssh/id_dsa.pub",QDir::homePath ()+"/.ssh/id_dsa");
    }
private slots:
    void connected(){
        qDebug()<<"connected!";
        chan=client.openProcessChannel();
        chan->requestPty(QxtSshProcess::Vt102Terminal);
        chan->startShell();
        connect(chan,SIGNAL(readyRead()),this,SLOT(readyRead()));
        connect(&stdio,SIGNAL(readyRead()),this,SLOT(stdio_readyRead()));
    }
    void authenticationRequired(QList<QxtSshClient::AuthenticationMethod> availableMethods){
        qDebug()<<"Authentications that can continue:";
        foreach(QxtSshClient::AuthenticationMethod meth, availableMethods){
            qDebug()<<"\t"<<meth;
        }
        stdio.write("password:");
        QTextStream qin(stdin);
        client.setPassphrase(qin.readLine());
    }
    void error (QxtSshClient::Error error){
        qDebug()<<"error"<<error;
        if(error==QxtSshClient::HostKeyUnknownError){
            QxtSshKey k=client.hostKey();
            qDebug()<<"The authenticity of host"<<client.hostName()<<"can't be established.";
            qDebug()<<k.type<<"key fingerprint is:"<<k.hash.toHex();
            stdio.write("Are you sure you want to continue connecting (yes/no)?:");
            QTextStream qin(stdin);
            if(qin.readLine().trimmed()=="yes"){
                client.loadKnownHosts(QDir::homePath ()+"/.ssh/known_hosts");
                // fixme, the above line should not be needed
                // the reason it is here, is because we can not store the internal libssh2 structure
                // between buildup/teardown
                // this can be fixed storing the key ourselfs

                client.addKnownHost(client.hostName(),k);
                QUrl u=QUrl::fromUserInput(qApp->arguments().at(1));
                client.connectToHost(u.userName(),u.host());
            }
        };

    }
    void readyRead(){
        stdio.write(chan->readAll());
    }
    void stdio_readyRead(){
        chan->write(stdio.readAll());
    }
private:
    QxtSshClient client;
    QxtSshProcess * chan;
    QxtStdio  stdio;
};

int main(int argc,char **argv){

    #ifdef Q_OS_UNIX
    termios term, restore;
    tcgetattr(1, &term);
    tcgetattr(1, &restore);
    term.c_lflag &= ~(ICANON | ECHO);
    //term.c_iflag &= ~ICRNL;
    term.c_lflag |= ISIG;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(1, 0, &term);
    #endif

    QCoreApplication app(argc,argv);
    if(app.arguments().count() <2){
        qDebug("usage: qxtssh <user>@<hostname> ");
        return 2;
    }
    QxtSshTest t;


    int ret=app.exec();
    #ifdef Q_OS_UNIX
    tcsetattr(1, 0, &restore);
    #endif
    return ret;
}

#include "main.moc"

