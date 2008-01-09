#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDataStream>
#include <QDebug>

struct XmlNode
{
    QString name;
    QString value;
    int type;
};
Q_DECLARE_METATYPE(XmlNode);

QDataStream &operator<<(QDataStream &out,const XmlNode &c);
QDataStream &operator>>(QDataStream &in, XmlNode &c );

QDebug operator<<(QDebug dbg, const XmlNode &c);




#endif

