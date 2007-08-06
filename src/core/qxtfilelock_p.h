#ifndef QXTFILELOCK_P_H_INCLUDED
#define QXTFILELOCK_P_H_INCLUDED

#include "qxtpimpl.h"
#include <QMutex>
#include <QMutexLocker>
#include <QLinkedList>
#include <QPointer>

class QxtFileLock;

/*!
 * \internal this class is used on *nix to register all locks created by a process and to let locks on *nix act like locks on windows
 * \internal the mutex is NOT locked automatically first lock mutex then call canRegisterLock -> real File Lock -> registerLock -> unlock mutex
 */
class QxtFileLockRegistry
{
    public:
        bool canRegisterLock(QxtFileLock *lock);
        QxtFileLockRegistry& instance();
        
        QLinkedList < QPointer<QxtFileLock> > procLocks;
        QMutex registryMutex;
        
    private:
        QxtFileLockRegistry();
};


class QxtFileLockPrivate : public QxtPrivate<QxtFileLock>
{
    public:
        QxtFileLockPrivate();
        QXT_DECLARE_PUBLIC(QxtFileLock);
        
        off_t offset;
        off_t length;
        int mode;
};
#endif
