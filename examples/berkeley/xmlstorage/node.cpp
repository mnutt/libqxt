#include "node.h"



QDataStream &operator<<(QDataStream &out,const XmlNode &c)
{
    out<<c.name;
    out<<c.value;
    out<<c.type;
    return out;
}
QDataStream &operator>>(QDataStream &in, XmlNode &c )
{
    in>>c.name;
    in>>c.value;
    in>>c.type;
    return in;
}

QDebug operator<<(QDebug dbg, const XmlNode &c)
{
    dbg.nospace() << "(" << c.name << ", " << c.value << ")";
    return dbg.space();
} 

