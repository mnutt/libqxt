#include "qxtsendmail.h"

 #include <QProcess>


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



