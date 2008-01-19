#ifndef QXTIRCPEER_H
#define QXTIRCPEER_H

#include <QxtRPCPeer>

struct IRCName 
{
    IRCName(QByteArray nick = QByteArray(), QByteArray ident = QByteArray(), QByteArray host = QByteArray());
    QByteArray nick;
    QByteArray ident;
    QByteArray host;
    QByteArray assemble() const;
    static IRCName fromName(const QByteArray& name);
};
Q_DECLARE_METATYPE(IRCName)

class IRCPeer : public QxtRPCPeer 
{
Q_OBJECT
public:
    IRCPeer(QObject* parent = 0);

    virtual QByteArray serialize(QString fn, QVariant p1, QVariant p2, QVariant p3, QVariant p4, QVariant p5, QVariant p6, QVariant p7, QVariant p8, QVariant p9) const;
    virtual QPair<QString, QList<QVariant> > deserialize(QByteArray& data);
    virtual bool canDeserialize(const QByteArray& buffer) const;
};

#endif
