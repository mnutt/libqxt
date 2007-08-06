#ifndef QXTFILELOCK_H_INCLUDED
#define QXTFILELOCK_H_INCLUDED


#include <QFile>
#include <QObject>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtFileLockPrivate;

class QXT_CORE_EXPORT QxtFileLock : public QObject
{
    Q_OBJECT
            
    public:
        
        enum Lockmode
        {
            ReadLockWait,
            ReadLock,
            WriteLockWait,
            WriteLock
        };
        
        QxtFileLock(QFile *file, const off_t offset,const off_t length,const int mode = WriteLockWait);
        ~QxtFileLock();
        off_t offset();
        off_t length();
        bool locked();
        QFile *file();
        
    public slots:
        bool lock();
        bool unlock();
        
    private:
        QXT_DECLARE_PRIVATE(QxtFileLock);
};




#endif