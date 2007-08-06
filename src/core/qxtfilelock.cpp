#include "qxtfilelock.h"
#include "qxtfilelock_p.h"

 QxtFileLockRegistry::QxtFileLockRegistry()
{
}

QxtFileLockRegistry& QxtFileLockRegistry::instance()
{
    static QxtFileLockRegistry instance;
    return instance;
}

bool QxtFileLockRegistry::canRegisterLock(QxtFileLock * lock)
{
    return false;
}

QxtFileLockPrivate::QxtFileLockPrivate()  : offset(0), length(0), mode(QxtFileLock::WriteLockWait)
{
    
}

 QxtFileLock::QxtFileLock(QFile *file,const off_t offset,const off_t length,const int mode) : QObject(file)
{
    QXT_INIT_PRIVATE(QxtFileLock);
    connect(file,SIGNAL(aboutToClose()),this,SLOT(unlock()));
}

QxtFileLock::~QxtFileLock()
{
    unlock();
}

off_t QxtFileLock::offset()
{
    return 0;
}

bool QxtFileLock::locked()
{
    return false;
}

off_t QxtFileLock::length()
{
    return 0;
}

bool QxtFileLock::unlock()
{
    return false;
}

bool QxtFileLock::lock()
{
    return false;
}

QFile * QxtFileLock::file()
{
    return qobject_cast<QFile *>(parent());
}