#ifndef QXTFILELOCK_P_H_INCLUDED
#define QXTFILELOCK_P_H_INCLUDED

#include "qxtpimpl.h"
#include <QMutex>
#include <QMutexLocker>
#include <QLinkedList>
#include <QPointer>

class QxtFileLock;

class QxtFileLockPrivate : public QxtPrivate<QxtFileLock>
{
    public:
        QxtFileLockPrivate();
        QXT_DECLARE_PUBLIC(QxtFileLock);
        
        off_t offset;
        off_t length;
        QxtFileLock::Mode mode;
        bool isLocked;
};
#endif
