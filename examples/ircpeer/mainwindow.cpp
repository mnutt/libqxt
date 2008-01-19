#include "mainwindow.h"

#include <QtGui>
MainWindow::MainWindow()
{
    centralwidget = new QWidget(this);
    gridLayout = new QGridLayout(centralwidget);
    tabWidget = new QTabWidget(centralwidget);
    gridLayout->addWidget(tabWidget, 0, 0, 1, 2);
    pushButton = new QPushButton(centralwidget);
    gridLayout->addWidget(pushButton, 1, 1, 1, 1);

    lineEdit = new QLineEdit(centralwidget);
    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

    setCentralWidget(centralwidget);
    menubar = new QMenuBar(this);
    setMenuBar(menubar);

    QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(send()));
    QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(send()));

    irc.attachSlot("PRIVMSG",this, SLOT(receiveMessage(IRCName, QByteArray, QByteArray)));
    irc.attachSignal(this, SIGNAL(sendMessage(IRCName, QByteArray, QByteArray)), "PRIVMSG");
    QObject::connect(&irc, SIGNAL(peerConnected()), this, SLOT(peerConnected()));
    QObject::connect(&irc, SIGNAL(peerError( QAbstractSocket::SocketError)), this, SLOT(peerError( QAbstractSocket::SocketError)));


    connect(this, SIGNAL(sendMessage(IRCName, QByteArray, QByteArray)), this, SLOT(receiveMessage(IRCName, QByteArray, QByteArray)));


    setWindowTitle("Qxt RPC IRC example");


    pushButton->setText("send");

    resize(800,600);

    QTimer::singleShot(0,this,SLOT(lateInit()));
}

void MainWindow::lateInit()
{
    if(condiag.exec())
    {
        irc.connect(condiag.hostname(), condiag.port());
        receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),
            "connecting to "+condiag.hostname()+":"+QByteArray::number(condiag.port()));
    }
}


void MainWindow::peerConnected()
{
    irc.call("USER", QVariant(), condiag.nickname(), condiag.hostname(), 
        condiag.hostname(), QByteArray("QxtRPCPeer"));

    irc.call("NICK", QVariant(), condiag.nickname());

    receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),"connected. type /join #channel, to join a channel");

    lineEdit->setFocus ( Qt::OtherFocusReason);

}
void MainWindow::peerError ( QAbstractSocket::SocketError e)
{
    receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),"QAbstractSocket::SocketError "+QByteArray::number(e));
}



void MainWindow::receiveMessage(IRCName nick, QByteArray channel, QByteArray message)
{
    if(!channels.contains(channel))
    {
        channels[channel] = new QTextBrowser();
        channels[channel]->setFrameShape(QFrame::NoFrame);
        tabWidget->addTab(channels[channel], channel);
    }
    channels[channel]->append(QString::fromUtf8(QByteArray("<") + nick.nick + "> " + message));
    channels[channel]->moveCursor(QTextCursor::End);
    channels[channel]->ensureCursorVisible();
}


void MainWindow::send()
{
    QByteArray msg=lineEdit->text().toUtf8();

    if(msg.startsWith('/'))
    {
        if(msg.startsWith("/join "))
        {
            irc.call("JOIN", QVariant(),msg.mid(6));

            receiveMessage(IRCName(condiag.hostname()),msg.mid(6),"you have joined "+msg.mid(6));        
            tabWidget->setCurrentWidget(channels[msg.mid(6)]);
        }
        else
        {
            receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),"unknown command "+msg);
        }
    }
    else
    {
        emit sendMessage  (IRCName(condiag.nickname().toUtf8()),
                tabWidget->tabText(tabWidget->currentIndex()).toUtf8(), msg);
    }

    lineEdit->clear();
}



