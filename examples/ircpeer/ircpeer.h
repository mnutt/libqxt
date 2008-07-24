#ifndef QXTIRCPEER_H
#define QXTIRCPEER_H

#include <QxtRPCPeer>
#include <qxtabstractsignalserializer.h>

struct IRCName {
    IRCName(QByteArray nick = QByteArray(), QByteArray ident = QByteArray(), QByteArray host = QByteArray());
    QByteArray nick;
    QByteArray ident;
    QByteArray host;
    QByteArray assemble() const;
    static IRCName fromName(const QByteArray& name);
};
Q_DECLARE_METATYPE(IRCName)

class IRCSerializer : public QxtAbstractSignalSerializer {
public:
    IRCSerializer();
    virtual QByteArray serialize(const QString& fn, const QVariant& p1 = QVariant(), const QVariant& p2 = QVariant(), const QVariant& p3 = QVariant(),
                                 const QVariant& p4 = QVariant(), const QVariant& p5 = QVariant(), const QVariant& p6 = QVariant(),
                                 const QVariant& p7 = QVariant(), const QVariant& p8 = QVariant()) const;
    virtual DeserializedData deserialize(QByteArray& data);
    virtual bool canDeserialize(const QByteArray& buffer) const;
};

#endif
