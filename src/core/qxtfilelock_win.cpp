#include "qxtfilelock.h"

bool QxtFileLock::unlock()
{
	qWarning("QxtFileLock::unlock() not implemented on Windows");
	return false;
}

bool QxtFileLock::lock()
{
	qWarning("QxtFileLock::lock() not implemented on Windows");
	return false;
}
