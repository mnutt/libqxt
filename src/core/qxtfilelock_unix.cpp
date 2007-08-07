#include "qxtfilelock.h"
#include "qxtfilelock_p.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <QPointer>
#include <QMutableLinkedListIterator>

/*!
 * \internal this class is used on *nix to register all locks created by a process and to let locks on *nix act like locks on windows
 * \internal the mutex is NOT locked automatically first lock mutex then call canRegisterLock -> real File Lock -> registerLock -> unlock mutex
 */
class QxtFileLockRegistry
{
    public:
        bool registerLock(QxtFileLock *lock);
        bool removeLock(QxtFileLock *lock);
        static QxtFileLockRegistry& instance();
                
    private:
        QLinkedList < QPointer<QxtFileLock> > procLocks;
        QMutex registryMutex;
        QxtFileLockRegistry();
};

 QxtFileLockRegistry::QxtFileLockRegistry()
{
}

QxtFileLockRegistry& QxtFileLockRegistry::instance()
{
    static QxtFileLockRegistry instance;
    return instance;
}

/*!
 * \internal this function locks the lockregistry and checks if there is a collision between the process locks
 * \internal if there is no collision it inserts the lock into the registry and returns
 * \internal return true for success
 */
bool QxtFileLockRegistry::registerLock(QxtFileLock * lock)
{
    QMutexLocker locker(&this->registryMutex);
    
    QFile *fileToLock = lock->file();
    
    if(fileToLock)
    {
       struct stat fileInfo;
        if( fstat(fileToLock->handle(),&fileInfo) < 0 )
            return false;
        
        int newLockStart = lock->offset();
        int newLockEnd = lock->offset()+lock->length();
        
        QMutableLinkedListIterator< QPointer<QxtFileLock> >iterator(this->procLocks);
        
        while(iterator.hasNext())
        {
            QPointer<QxtFileLock> currLock = iterator.next();
            if(currLock)
            {
                struct stat currFileInfo;
                
                /*first check if the current lock is on the same file*/
                if( fstat(currLock->file()->handle(),&currFileInfo) < 0 )
                {
                    Q_ASSERT(false);
                    continue;
                }
                    
                if(currFileInfo.st_dev == fileInfo.st_dev && currFileInfo.st_ino == fileInfo.st_ino)
                {
                    /*same file, check if our locks are in conflict*/
                    int currLockStart = currLock->offset();
                    int currLockEnd = currLock->offset()+currLock->length();
                    
                    /*do we have to check for threads here?*/
                    if(newLockStart >= currLockStart && newLockStart <= currLockEnd ||
                        newLockEnd >= currLockStart && newLockEnd <= currLockEnd )
                    {
                        /*same lock region if one of both locks are exclusive we have a collision*/
                        if(lock->mode() == QxtFileLock::WriteLockWait || lock->mode() == QxtFileLock::WriteLock ||
                           currLock->mode() == QxtFileLock::WriteLockWait || currLock->mode() == QxtFileLock::WriteLock)
                            return false;
                    }
                }
            }
            else //remove dead locks
                iterator.remove();
        }
        
        /*here we can insert the lock into the list and return*/
        procLocks.append(QPointer<QxtFileLock>(lock));
        return true;
        
    }
    
    return false;
}

bool QxtFileLockRegistry::removeLock(QxtFileLock * lock)
{
    QMutexLocker locker(&this->registryMutex);
    procLocks.removeAll(lock);
    return true;
}

bool QxtFileLock::unlock()
{
    if(file() && file()->isOpen() && isActive())
    {
        /*first remove real lock*/
        
        QxtFileLockRegistry::instance().removeLock(this);
    }
    return false;
}

bool QxtFileLock::lock()
{
    if(file() && file()->isOpen())
    {
        if(QxtFileLockRegistry::instance().registerLock(this))
        {
            /*now get lock*/
        }
    }
    return false;
}

