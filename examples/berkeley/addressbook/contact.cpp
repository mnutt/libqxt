#include "contact.h"



QDataStream &operator<<(QDataStream &out,const Contact &c)
{
    out<<c.name;
    out<<c.phone;
    out<<c.address;
    return out;
}
QDataStream &operator>>(QDataStream &in, Contact &c )
{
    in>>c.name;
    in>>c.phone;
    in>>c.address;
    return in;
}


