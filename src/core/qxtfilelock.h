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
        
        enum Mode
        {
            ReadLockWait,
            ReadLock,
            WriteLockWait,
            WriteLock
        };
        
        QxtFileLock(QFile *file, const off_t offset,const off_t length,const QxtFileLock::Mode mode = WriteLockWait);
        ~QxtFileLock();
        
        off_t offset() const;
        off_t length() const;
        bool isActive() const;
        QFile *file() const;
        QxtFileLock::Mode mode() const;
        
    public slots:
        bool lock();
        bool unlock();
        
    private:
        QxtFileLock(const QxtFileLock &other);
        QXT_DECLARE_PRIVATE(QxtFileLock);
};
#endif
