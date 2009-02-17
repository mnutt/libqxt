#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

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


#endif // NODE_H_INCLUDED

