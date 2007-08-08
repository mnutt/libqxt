#ifndef QXTBOUNDFUNCTION_H
#define QXTBOUNDFUNCTION_H

#include <QObject>
#include <QMetaObject>
#include <QGenericArgument>
#include <qxtmetaobject.h>

class QxtBoundFunction : public QObject {
Q_OBJECT
public:
    template <class T>
    QxtNullable<T> invoke(QXT_PROTO_10ARGS(QVariant));

    template <class T>
    QxtNullable<T> invoke(Qt::ConnectionType type, QXT_PROTO_10ARGS(QVariant));

    bool invoke(QXT_PROTO_10ARGS(QVariant));
    bool invoke(Qt::ConnectionType, QXT_PROTO_10ARGS(QVariant));
    bool invoke(QXT_PROTO_10ARGS(QGenericArgument)); 
    bool invoke(QGenericReturnArgument returnValue, QXT_PROTO_10ARGS(QGenericArgument));
    bool invoke(Qt::ConnectionType type, QXT_PROTO_10ARGS(QGenericArgument));

    virtual bool invoke(Qt::ConnectionType type, QGenericReturnArgument returnValue,
            QXT_PROTO_10ARGS(QGenericArgument)) = 0;
};


#endif
