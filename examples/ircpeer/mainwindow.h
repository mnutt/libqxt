#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED
#include <QtGui>
#include <QHash>
#include "ircpeer.h"
#include "dialog.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow();
protected:
    bool eventFilter(QObject* obj, QEvent* event);
private slots:
    void lateInit();
    void peerConnected();
    void peerError(QAbstractSocket::SocketError);
    void receiveMessage(IRCName, QByteArray, QByteArray);
    void receiveNotice(IRCName, QByteArray, QByteArray);
    void receiveAction(IRCName, QByteArray, QByteArray);
    void userJoin(IRCName, QByteArray);
    void userPart(IRCName, QByteArray);
    void userQuit(IRCName, QByteArray);
    void logMessage(IRCName, QByteArray, QByteArray, QString);
    void send();
    void tabActivated(int index);
    void partCurrentChannel();
    void pong(IRCName, QByteArray);
signals:
    void sendMessage(IRCName, QByteArray, QByteArray);
private:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QHash <QByteArray,QTextBrowser*> channels;
    QxtRPCPeer irc;
    ConnectDialog condiag;
};
#endif // MAINWINDOW_H_INCLUDED
