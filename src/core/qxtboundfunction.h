#ifndef QXTBOUNDFUNCTION_H
#define QXTBOUNDFUNCTION_H

#include <QObject>
#include <QMetaObject>
#include <QGenericArgument>
#include <qxtmetaobject.h>
#include <qxtnull.h>
#include <QThread>

class QxtBoundFunction : public QObject {
Q_OBJECT
public:
    template <class T>
    inline QxtNullable<T> invoke(QXT_PROTO_10ARGS(QVariant)) {
        if(QThread::currentThread() == parent()->thread())
            return invoke<T>(Qt::DirectConnection, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
        return invoke<T>(Qt::BlockingQueuedConnection, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }

    template <class T>
    QxtNullable<T> invoke(Qt::ConnectionType type, QXT_PROTO_10ARGS(QVariant)) {
        if(type == Qt::QueuedConnection) {
            qWarning() << "QxtBoundFunction::invoke: Cannot return a value using a queued connection";
            return qxtNull;
        }
        T retval;
        // I know this is a totally ugly function call
        if(invoke(type, QGenericReturnArgument(qVariantFromValue<T>(*reinterpret_cast<T*>(0)).typeName(), reinterpret_cast<void*>(&retval)),
                  p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)) {
            return retval;
        } else {
            return qxtNull;
        }
    }

    inline bool invoke(QXT_PROTO_10ARGS(QVariant)) {
        return invoke(Qt::AutoConnection, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
    bool invoke(Qt::ConnectionType, QXT_PROTO_10ARGS(QVariant));

    inline bool invoke(QXT_PROTO_10ARGS(QGenericArgument)) {
        return invoke(Qt::AutoConnection, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
    bool invoke(Qt::ConnectionType type, QXT_PROTO_10ARGS(QGenericArgument));

    inline bool invoke(QGenericReturnArgument returnValue, QXT_PROTO_10ARGS(QVariant)) {
        return invoke(Qt::AutoConnection, returnValue, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
    bool invoke(Qt::ConnectionType type, QGenericReturnArgument returnValue, QXT_PROTO_10ARGS(QVariant));

    inline bool invoke(QGenericReturnArgument returnValue, QXT_PROTO_10ARGS(QGenericArgument)) {
        return invoke(Qt::AutoConnection, returnValue, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
    virtual bool invoke(Qt::ConnectionType type, QGenericReturnArgument returnValue, QXT_PROTO_10ARGS(QGenericArgument)) = 0;

protected:
    QxtBoundFunction(QObject* parent = 0);
};


#endif
