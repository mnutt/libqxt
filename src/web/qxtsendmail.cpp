#include "qxtsendmail.h"

 #include <QProcess>

/*!
        \class QxtSendmail QxtSendmail
        \ingroup QxtWeb
        \brief can send your QxtMail using the local sendmail program 
*/


bool QxtSendmail::send(QxtMail  mail)
{
    QProcess sendmail;
    sendmail.start("sendmail",QStringList()<<"-t");
    sendmail.waitForStarted ();
    sendmail.write(mail.rfc822().toLocal8Bit());
    sendmail.closeWriteChannel();
    sendmail.waitForFinished ();
    return (sendmail.exitCode()==0);
}



