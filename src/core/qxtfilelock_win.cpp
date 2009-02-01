/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE. 
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
** 
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#ifdef WIN32

#include "qxtfilelock.h"
#include "qxtfilelock_p.h"
#include <windows.h>
#include <io.h>

bool QxtFileLock::unlock()
{
    if (file() && file()->isOpen() && isActive())
    {
        HANDLE w32FileHandle;
        OVERLAPPED ov1;
        DWORD dwflags;

        w32FileHandle = (HANDLE)_get_osfhandle(file()->handle());
        if (w32FileHandle == INVALID_HANDLE_VALUE)
            return false;

        memset(&ov1, 0, sizeof(ov1));
        ov1.Offset =  qxt_d().offset;

        if (UnlockFileEx(w32FileHandle, 0, qxt_d().length, 0, &ov1))
        {
            qxt_d().isLocked = false;
            return true;
        }
    }
    return false;
}

bool QxtFileLock::lock()
{
    if (file() && file()->isOpen() && !isActive())
    {
        HANDLE w32FileHandle;
        OVERLAPPED ov1;
        DWORD dwflags;

        w32FileHandle = (HANDLE)_get_osfhandle(file()->handle());
        if (w32FileHandle == INVALID_HANDLE_VALUE)
            return false;

        switch (qxt_d().mode)
        {
        case    ReadLock:
            dwflags = LOCKFILE_FAIL_IMMEDIATELY;
            break;

        case    ReadLockWait:
            dwflags = 0;
            break;

        case    WriteLock:
            dwflags = LOCKFILE_EXCLUSIVE_LOCK | LOCKFILE_FAIL_IMMEDIATELY;
            break;

        case    WriteLockWait:
            dwflags = LOCKFILE_EXCLUSIVE_LOCK;
            break;

        default:
            return (false);
        }

        memset(&ov1, 0, sizeof(ov1));
        ov1.Offset =  qxt_d().offset;

        if (LockFileEx(w32FileHandle, dwflags, 0,  qxt_d().length, 0, &ov1))
        {
            qxt_d().isLocked = true;
            return true;
        }
    }
    return false;
}

#endif

