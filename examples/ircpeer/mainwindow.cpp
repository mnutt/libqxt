#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow(0) {
    centralwidget = new QWidget(this);
    gridLayout = new QGridLayout(centralwidget);
    tabWidget = new QTabWidget(centralwidget);
    tabWidget->setTabPosition(QTabWidget::South);
    gridLayout->addWidget(tabWidget, 0, 0, 1, 2);
    pushButton = new QPushButton("&Send", centralwidget);
    gridLayout->addWidget(pushButton, 1, 1, 1, 1);

    lineEdit = new QLineEdit(centralwidget);
    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);
    setCentralWidget(centralwidget);

    QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(send()));
    QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(send()));
    QObject::connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabActivated(int)));
    lineEdit->installEventFilter(this);

    irc.setSerializer(new IRCSerializer);
    irc.attachSlot("PRIVMSG",this, SLOT(receiveMessage(IRCName, QByteArray, QByteArray)));
    irc.attachSlot("NOTICE",this, SLOT(receiveNotice(IRCName, QByteArray, QByteArray)));
    irc.attachSlot("JOIN",this, SLOT(userJoin(IRCName, QByteArray)));
    irc.attachSlot("PART",this, SLOT(userPart(IRCName, QByteArray)));
    irc.attachSlot("QUIT",this, SLOT(userQuit(IRCName, QByteArray)));
    irc.attachSlot("PING",this, SLOT(pong(IRCName, QByteArray)));
    irc.attachSlot("CTCP-ACTION",this, SLOT(receiveAction(IRCName, QByteArray, QByteArray)));
    irc.attachSlot("system",this, SLOT(receiveMessage(IRCName, QByteArray, QByteArray)));
    irc.attachSlot("numeric",this, SLOT(receiveMessage(IRCName, QByteArray, QByteArray)));
    irc.attachSignal(this, SIGNAL(sendMessage(IRCName, QByteArray, QByteArray)), "PRIVMSG");
    QObject::connect(&irc, SIGNAL(connectedToServer()), this, SLOT(peerConnected()));
    QObject::connect(&irc, SIGNAL(serverError(QAbstractSocket::SocketError)), this, SLOT(peerError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(sendMessage(IRCName, QByteArray, QByteArray)), this, SLOT(receiveMessage(IRCName, QByteArray, QByteArray)));

    setWindowTitle("Qxt RPC IRC example");
    resize(800,600);
    QTimer::singleShot(0,this,SLOT(lateInit()));
}

void MainWindow::lateInit() {
    if(condiag.exec()) {
        irc.connect(condiag.hostname(), condiag.port());
        receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),
            "connecting to "+condiag.hostname()+':'+QByteArray::number(condiag.port()));
    } else {
        qApp->quit();
    }
}

void MainWindow::pong(IRCName, QByteArray key) {
    irc.call("PONG", QVariant(), key);
}

void MainWindow::peerConnected() {
    irc.call("USER", QVariant(), condiag.nickname(), condiag.hostname(), condiag.hostname(), QByteArray("QxtRPCPeer"));
    irc.call("NICK", QVariant(), condiag.nickname());

    receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),"connected. type /join #channel, to join a channel");
    lineEdit->setFocus(Qt::OtherFocusReason);
}
void MainWindow::peerError(QAbstractSocket::SocketError e) {
    receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),"QAbstractSocket::SocketError "+QByteArray::number(e));
}

void MainWindow::receiveMessage(IRCName nick, QByteArray channel, QByteArray message) {
    if(message.startsWith(QByteArray("\001ACTION ")))
        receiveAction(nick, channel, message.mid(8, message.size()-9));
    else
        logMessage(nick, channel, message, "<%1> %2");
}

void MainWindow::receiveNotice(IRCName nick, QByteArray channel, QByteArray message) {
    logMessage(nick, channel, message, "[%1] %2");
}

void MainWindow::receiveAction(IRCName nick, QByteArray channel, QByteArray message) {
    logMessage(nick, channel, message, "* %1 %2");
}

void MainWindow::userJoin(IRCName nick, QByteArray channel) {
    if(channels.contains(nick.nick))
        logMessage(nick, nick.nick, channel, "! %1 joined %2");
    logMessage(nick, channel, "joined the channel", "! %1 %2");
}

void MainWindow::userPart(IRCName nick, QByteArray channel) {
    if(nick.nick == condiag.nickname()) return;
    logMessage(nick, channel, "left the channel", "! %1 %2");
}

void MainWindow::userQuit(IRCName nick, QByteArray message) {
    if(channels.contains(nick.nick))
        logMessage(nick, nick.nick, message, "! %1 Quit: %2");
    logMessage(nick, "", message, "! %1 Quit: %2");
}

void MainWindow::logMessage(IRCName nick, QByteArray channel, QByteArray message, QString format) {
    if(channel == condiag.nickname()) {
        if(channel == nick.nick)
            channel = condiag.hostname();
        else
            channel = nick.nick;
    }
    if(channel.isEmpty() || channel == "AUTH") {
        channel = condiag.hostname();
    } else if(!channels.contains(channel)) {
        channels[channel] = new QTextBrowser();
        channels[channel]->setFrameShape(QFrame::NoFrame);
        tabWidget->addTab(channels[channel], channel);
    }
    channels[channel]->append(format.arg(QString(nick.nick)).arg(QString(message)));
    channels[channel]->moveCursor(QTextCursor::End);
    channels[channel]->ensureCursorVisible();
    int index = tabWidget->indexOf(channels[channel]);
    if(index != tabWidget->currentIndex())
        tabWidget->setTabIcon(index, qApp->style()->standardIcon(QStyle::SP_ArrowRight));
    qApp->alert(this, 250);
}

void MainWindow::send() {
    QByteArray msg=lineEdit->text().toUtf8();
    if(msg.trimmed().isEmpty()) return;

    if(msg.startsWith('/')) {
        if(msg.startsWith(QByteArray("/join "))) {
            if(msg.mid(6,1) == "#" || msg.mid(6,1) == "&")
                irc.call("JOIN", QVariant(),msg.mid(6));

            receiveMessage(IRCName(condiag.hostname()),msg.mid(6),"you have joined "+msg.mid(6));        
            tabWidget->setCurrentWidget(channels[msg.mid(6)]);
        } else if(msg.startsWith(QByteArray("/me "))) {
            emit sendMessage(IRCName(condiag.nickname().toUtf8()),
                    tabWidget->tabText(tabWidget->currentIndex()).toUtf8(),
                    QByteArray("\001ACTION " + msg.mid(4) + "\001"));
        } else if(msg.startsWith(QByteArray("/names"))) {
            if(msg == "/names")
                irc.call("NAMES", QVariant(), tabWidget->tabText(tabWidget->currentIndex()).toUtf8());
            else
                irc.call("NAMES", QVariant(), msg.mid(7));
        } else if(msg == "/part") {
            partCurrentChannel();
        } else if(msg.startsWith(QByteArray("/raw "))) {
            irc.call("raw", msg.mid(5));
        } else if(msg == "/quit") {
            qApp->quit();
        } else {
            receiveMessage(IRCName(condiag.hostname()),condiag.hostname(),"unknown command "+msg);
        }
    } else {
        emit sendMessage(IRCName(condiag.nickname().toUtf8()),
                tabWidget->tabText(tabWidget->currentIndex()).toUtf8(), msg);
    }

    lineEdit->clear();
}

void MainWindow::partCurrentChannel() {
    if(tabWidget->currentIndex() == 0) return;
    if(tabWidget->tabText(tabWidget->currentIndex())[0] == '#' || tabWidget->tabText(tabWidget->currentIndex())[0] == '&')
        irc.call("PART", QVariant(), tabWidget->tabText(tabWidget->currentIndex()).toUtf8());
    channels.remove(tabWidget->tabText(tabWidget->currentIndex()).toUtf8());
    tabWidget->currentWidget()->deleteLater();
    tabWidget->removeTab(tabWidget->currentIndex());
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if(obj != lineEdit) return false;
    if(event->type() != QEvent::KeyPress) return false;
    QKeyEvent* ke = static_cast<QKeyEvent*>(event);
    if(ke->key() == Qt::Key_PageUp || ke->key() == Qt::Key_PageDown) {
        QScrollBar* scroll = qobject_cast<QTextBrowser*>(tabWidget->currentWidget())->verticalScrollBar();
        if(ke->key() == Qt::Key_PageUp)
            scroll->triggerAction(QScrollBar::SliderPageStepSub);
        else
            scroll->triggerAction(QScrollBar::SliderPageStepAdd);
        return true;
    }
    if(ke->modifiers().testFlag(Qt::ControlModifier) && (ke->key() == Qt::Key_F4 || ke->key() == Qt::Key_W)) {
        partCurrentChannel();
        return true;
    }
    if(ke->key() != Qt::Key_Tab && ke->key() != Qt::Key_Backtab) return false;
    if(!ke->modifiers().testFlag(Qt::ControlModifier)) return false;
    int nextTab = tabWidget->currentIndex();
    if(ke->key() == Qt::Key_Backtab)
        nextTab--;
    else
        nextTab++;
    if(nextTab == -1) nextTab = tabWidget->count() - 1;
    if(nextTab == tabWidget->count()) nextTab = 0;
    tabWidget->setCurrentIndex(nextTab);
    return true;
}

void MainWindow::tabActivated(int index) {
    tabWidget->setTabIcon(index, QIcon());
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow main;
    main.show();
    return app.exec();
}
