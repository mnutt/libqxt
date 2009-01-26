#include "qxtmail.h"


/*!
        \class QxtMail QxtMail
        \ingroup QxtWeb
        \brief Implicit shared contianer, reflecting a rfc822 mail



        \doqsy {implicitshared}

*/


struct QxtMailPrivate
{
    QStringList recipients;
    QString     subject;
    QString     body;
    QString     sender;
    QStringList extraHeaders;
};



QxtMail::QxtMail()
{
    qxt_d = new QxtMailPrivate;
}

QxtMail::QxtMail(const QStringList& recipients,
                 const QString& subject, const QString& body,
                 const QStringList& extraHeaders)
{
    qxt_d = new QxtMailPrivate;
    setRecipients(recipients);
    setSubject(subject);
    setBody(body);
    setExtraHeaders(extraHeaders);
}

QStringList QxtMail::recipients()    const
{
    return qxt_d().recipients;
}
QString     QxtMail::sender()    const
{
    return qxt_d().sender;
}

QString     QxtMail::subject()       const
{
    return qxt_d().subject;
}

QString     QxtMail::body()          const
{
    return qxt_d().body;
}

QStringList QxtMail::extraHeaders()  const
{
    return qxt_d().extraHeaders;

}

void QxtMail::setRecipients(QStringList a)
{
    qxt_d().recipients = a;

}
void QxtMail::setSender(QString a)
{
    qxt_d().sender = a;

}
void QxtMail::setSubject(QString a)
{
    qxt_d().subject = a;

}

void QxtMail::setBody(QString a)
{
    qxt_d().body = a;

}

void QxtMail::setExtraHeaders(QStringList a)
{
    qxt_d().extraHeaders = a;
}

QString QxtMail::rfc822()
{
    QString e;
    foreach(const QString& r, recipients())
    {
        e += "TO:" + r + "\n";
    }

    e += "Subject:" + subject() + "\n";

    foreach(const QString& r, extraHeaders())
    {
        e += r + "\n";
    }

    if (!sender().isEmpty())
        e += "From:" + sender() + "\n";


    e += "\n" + body() + "\n";

    return e;
}
