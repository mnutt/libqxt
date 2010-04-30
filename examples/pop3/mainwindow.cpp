#include "mainwindow.h"
#include "qxtpop3command.h"
#include <QPair>
#include <QFileDialog>
#include <QFile>
#include <QSslSocket>




MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), pop(0), count(0), size(0), msg(0)
{
    setupUi(this);
    settings = new QSettings(QSettings::UserScope,"Qxt", "MailTest");
    pop = new QxtPop3(this);
    pop->sslSocket()->setProtocol(QSsl::TlsV1);
    pop->sslSocket()->setPeerVerifyMode(QSslSocket::QueryPeer);
    QString username = settings->value("username").toString();
    QString hostname = settings->value("hostname").toString();
    QString pass = settings->value("password").toString();
    int port = settings->value("port").toInt();
    bool ok;
    Encryption enc = Encryption(settings->value("encryption").toInt(&ok));
    if (!ok) enc = Clear;
    switch (enc)
    {
    case UseSSL:
        sslRadioButton->setChecked(true);
        break;
    case UseStartTLS:
        startTLSRadioButton->setChecked(true);
        break;
    case Clear:
    default:
        clearRadioButton->setChecked(true);
        break;
    }
    usernameLineEdit->setText(username);
    hostnameLineEdit->setText(hostname);
    passwordLineEdit->setText(pass);
    if (port != 0) portLineEdit->setText(QString::number(port));
    connect(connectPushButton, SIGNAL(clicked()), this, SLOT(connectToHost()));
    connect(settingsPushButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
    connect(pop, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(pop, SIGNAL(connected()), this, SLOT(connected()));
    connect(pop, SIGNAL(connectionFailed(QByteArray)), this, SLOT(handleSslError(QByteArray)));
    connect(pop, SIGNAL(encryptionFailed(QByteArray)), this, SLOT(handleSslError(QByteArray)));
    connect(pop, SIGNAL(authenticationFailed(QByteArray)), this, SLOT(handleAuthError(QByteArray)));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(newCmd()));
    help();
}

void MainWindow::newCmd()
{
    QxtPop3Command* cmd = 0;
    QString line = lineEdit->text();
    lineEdit->clear();
    QStringList words = line.split(" ", QString::SkipEmptyParts);
    if (words[0] == "quit")
    {
        if (!pop->isConnected()) return;
        cmd = pop->quit();
        connect(cmd, SIGNAL(completed(int)), this, SLOT(handleQuit(int)));
        plainTextEdit->appendPlainText("QUIT sent");
    }
    else if (words[0] == "stat")
    {
        if (!pop->isConnected()) return;
        cmd = pop->stat(count,size);
        connect(cmd, SIGNAL(completed(int)), this, SLOT(handleStat(int)));
        output("STAT sent");
    }
    else if (words[0] == "list")
    {
        if (!pop->isConnected()) return;
        list.clear();
        cmd = pop->messageList(list);
        connect(cmd, SIGNAL(completed(int)), this, SLOT(handleList(int)));
        output("LIST sent");
    }
    else if (words[0] == "retr")
    {
        if (!pop->isConnected()) return;
        if (words.length() < 2)
        {
            output("Usage: retr <which>");
            return;
        }
        int which = words[1].toInt();
        cmd = pop->retrieveMessage(which, msg);
        connect(cmd, SIGNAL(completed(int)), this, SLOT(handleRetr(int)));
        connect(cmd, SIGNAL(progress(int)), this, SLOT(progress(int)));
        output("RETR sent");
    }
    else if (words[0] == "dele")
    {
        if (!pop->isConnected()) return;
        if (words.length() < 2)
        {
            output("Usage: dele <which>");
            return;
        }
        int which = words[1].toInt();
        cmd = pop->deleteMessage(which);
        connect(cmd, SIGNAL(completed(int)), this, SLOT(handleDele(int)));
        output("DELE sent");
    }
    else if (words[0] == "reset")
    {
        if (!pop->isConnected()) return;
        cmd = pop->reset();
        connect(cmd, SIGNAL(completed(int)), this, SLOT(handleRset(int)));
        output("RSET sent");
    }
    else if (words[0] == "help")
    {
        help();
    }
    else if (words[0] == "saveatt")
    {
        if (msg == 0)
        {
            output("no current message.");
            return;
        }
        if (words.length() < 2)
        {
            output("Usage: saveatt <attachment name>");
            return;
        }
        if (!msg->attachments().contains(words[1]))
        {
            output(QString("no such attachment: ") + words[1]);
            return;
        }
        QxtMailAttachment att = msg->attachment(words[1]);
        QString filename = QFileDialog::getSaveFileName(this, "Save attachment", QString("./") + words[1]);
        if (!filename.isEmpty())
        {
            QFile file(filename);
            QIODevice::OpenMode flags = QIODevice::WriteOnly;
            if (att.isText()) flags |= QIODevice::Text;
            file.open(flags);
            file.write(att.rawData());
            file.close();
            output("Attachment saved");
        }
    }
    else
    {
        output("unhandled command");
    }
}


    void MainWindow::handleQuit(int code)
    {
        switch (code)
        {
        case QxtPop3Command::OK:
            output("QUIT: OK received");
//            close();
            break;
        case QxtPop3Command::Aborted:
            printError();
            output("QUIT aborted.");
            break;
        case QxtPop3Command::Timeout:
            output("QUIT: time out.");
            break;
        default:
            break;
        }
    }

    void MainWindow::handleStat(int code)
    {
        switch (code)
        {
        case QxtPop3Command::OK:
            output(QString("STAT: %1 messages, %2 bytes").arg(count).arg(size));
            break;
        case QxtPop3Command::Aborted:
            printError();
            output("STAT aborted.");
            break;
        case QxtPop3Command::Timeout:
            output("STAT: time out.");
            break;
        default:
            break;
        }
    }

    void MainWindow::handleList(int code)
    {
        switch (code)
        {
        case QxtPop3Command::OK:
            output("LIST: OK received");
            {
                QPair<int,int> msg;
                foreach (msg, list)
                {
                    output(QString("message %1: %2 bytes").arg(msg.first).arg(msg.second));
                }
            }
            break;
        case QxtPop3Command::Aborted:
            printError();
            output("LIST aborted.");
            break;
        case QxtPop3Command::Timeout:
            output("LIST: time out.");
            break;
        default:
            break;
        }
    }

    void MainWindow::handleRetr(int code)
    {
        switch (code)
        {
        case QxtPop3Command::OK:
            output("RETR: OK received");
            {
                output("------Message Headers:");
                foreach(QString key, msg->extraHeaders().keys())
                {
                    output(QString("%1: %2").arg(key, msg->extraHeader(key)));
                }
                output("------Message Body:");
                output(msg->body());
                if (msg->attachments().size() > 0)
                {
                    output("------Attachments:");
                    foreach(QString filename, msg->attachments().keys())
                    {
                        output(QString("%1: Content-Type = %2, %3 bytes")
                               .arg(filename)
                               .arg(msg->attachment(filename).contentType())
                               .arg(msg->attachment(filename).rawData().length()));
                    }
                }
                output("------End of Message\n");
            }
            break;
        case QxtPop3Command::Aborted:
            printError();
            output("RETR aborted.");
            break;
        case QxtPop3Command::Timeout:
            output("RETR: time out.");
            break;
        default:
            break;
        }
    }

    void MainWindow::handleDele(int code)
    {
        switch (code)
        {
        case QxtPop3Command::OK:
            output("DELE: OK received");
            break;
        case QxtPop3Command::Aborted:
            printError();
            output("DELE aborted.");
            break;
        case QxtPop3Command::Timeout:
            output("DELE: time out.");
            break;
        default:
            break;
        }
    }

    void MainWindow::handleRset(int code)
    {
        switch (code)
        {
        case QxtPop3Command::OK:
            output("RSET: OK received");
            break;
        case QxtPop3Command::Aborted:
            printError();
            output("RSET aborted.");
            break;
        case QxtPop3Command::Timeout:
            output("RSET: time out.");
            break;
        default:
            break;
        }
    }

    void MainWindow::printError()
    {
        QObject* s = sender();
        if (s != 0)
        {
            QxtPop3Command* cmd = qobject_cast<QxtPop3Command*>(s);
            if (cmd->status() == QxtPop3Command::Error)
            {
                output(cmd->error());
            }
        }
    }

    void MainWindow::help()
    {
        output("Available commands:");
        output("help: print this help message\n"
               "quit\n"
               "stat\n"
               "list\n"
               "retr <nb>\n"
               "dele <nb>\n"
               "reset\n"
               "saveatt <attachment name>: save attachment of last retrieved message\n");
    }

    void MainWindow::connectToHost()
    {
        QString hostname = hostnameLineEdit->text();
        bool useSSL = sslRadioButton->isChecked();
        if (startTLSRadioButton->isChecked())
        {
            pop->setStartTlsDisabled(false);
        }
        else
        {
            pop->setStartTlsDisabled(true);
        }
        bool ok;
        int port = portLineEdit->text().toInt(&ok);
        if (!ok || port == 0)
        { // default port
            if (useSSL)
            {
                port = 995;
            }
            else
            {
                port = 110;
            }
        }
        QString username = usernameLineEdit->text();
        QString pass = passwordLineEdit->text();
        pop->setUsername(username.toLocal8Bit());
        pop->setPassword(pass.toLocal8Bit());
        if (useSSL)
        {
            pop->connectToSecureHost(hostname.toLocal8Bit(), port);
        }
        else
        {
            pop->connectToHost(hostname.toLocal8Bit(), port);
        }
    }

    void MainWindow::saveSettings()
    {
        QString hostname = hostnameLineEdit->text();
        settings->setValue("hostname", hostname);
        Encryption enc;
        if(sslRadioButton->isChecked())
        {
            enc = UseSSL;
        }
        else if (startTLSRadioButton->isChecked())
        {
            enc = UseStartTLS;
        }
        else
        {
            enc = Clear;
        }
        settings->setValue("Encryption", enc);
        bool ok;
        int port = portLineEdit->text().toInt(&ok);
        if (ok && port != 0) settings->setValue("port", port);
        QString username = usernameLineEdit->text();
        settings->setValue("username", username);
        QString pass = passwordLineEdit->text();
        settings->setValue("password", pass);
        settings->sync();
    }

    void MainWindow::connected()
    {
        connectPushButton->setDisabled(true);
        output("Connected to host");
    }

    void MainWindow::disconnected()
    {
        connectPushButton->setEnabled(true);
        output("Disconnected from Host");
    }

    void MainWindow::handleSslError(const QByteArray& msg)
    {
        output(QString("Ssl handshake error: ") + msg);
    }

    void MainWindow::handleAuthError(const QByteArray& msg)
    {
        output(QString("Authentication error: ") + msg);
    }

    void MainWindow::progress(int percent)
    {
        output(QString("Progress: %1%%").arg(percent));
    }
