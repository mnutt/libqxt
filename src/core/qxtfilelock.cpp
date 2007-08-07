#include "qxtfilelock.h"
#include "qxtfilelock_p.h"

QxtFileLockPrivate::QxtFileLockPrivate()  : offset(0), length(0), mode(QxtFileLock::WriteLockWait), isLocked(false)
{
    
}

 QxtFileLock::QxtFileLock(QFile *file,const off_t offset,const off_t length,const QxtFileLock::Mode mode) : QObject(file)
{
    QXT_INIT_PRIVATE(QxtFileLock);
    connect(file,SIGNAL(aboutToClose()),this,SLOT(unlock()));
}

QxtFileLock::~QxtFileLock()
{
    unlock();
}

off_t QxtFileLock::offset() const
{
    return qxt_d().offset;
}

bool QxtFileLock::isActive() const
{
    return qxt_d().isLocked;
}

off_t QxtFileLock::length() const
{
    return qxt_d().length;
}

QFile * QxtFileLock::file() const
{
    return qobject_cast<QFile *>(parent());
}

QxtFileLock::Mode QxtFileLock::mode() const
{
    return qxt_d().mode;
}