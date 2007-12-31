#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDataStream>

struct Contact
{
    QString name;
    QString phone;
    QString address;

};
Q_DECLARE_METATYPE(Contact);

QDataStream &operator<<(QDataStream &out,const Contact &c);
QDataStream &operator>>(QDataStream &in, Contact &c );


#endif

