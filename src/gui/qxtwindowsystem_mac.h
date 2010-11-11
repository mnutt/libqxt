/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtGui module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

/****************************************************************************
 **
 ** Copyright (C) Marcin Jakubowski <mjakubowski (at) gmail (dot) com
 **
 ** Defines some of required CoreGraphics private parts. This code may
 ** break at any time and uses *undocumented* features of Mac OS X.
 **
 ** Also defines QCFString, part of Qt code found in src/corelib/kernel
 ** qcoremac_p.h file.
 ****************************************************************************/

#ifndef QXTWINDOWSYSTEM_MAC_H
#define QXTWINDOWSYSTEM_MAC_H

//
//  CGSPrivate.h
//  Header file for undocumented CoreGraphics SPI
//
//  Arranged by Nicholas Jitkoff
//  Based on CGSPrivate.h by Richard Wareham
//
//  Contributors:
//    Austin Sarner: Shadows
//    Jason Harris: Filters, Shadows, Regions
//    Kevin Ballard: Warping
//    Steve Voida: Workspace notifications
//    Tony Arnold: Workspaces notifications enum filters
//    Ben Gertzfield: CGSRemoveConnectionNotifyProc
//
//  Changes:
//    2.3 - Added the CGSRemoveConnectionNotifyProc method with the help of Ben Gertzfield
//    2.2 - Moved back to CGSPrivate, added more enums to the CGSConnectionNotifyEvent
//    2.1 - Added spaces notifications
//    2.0 - Original Release

#include <Carbon/Carbon.h>

#define CGSConnectionID CGSConnection
#define CGSWindowID CGSWindow
#define CGSDefaultConnection _CGSDefaultConnection()

#ifdef __cplusplus
extern "C" {
#endif

  typedef int CGSConnection;
  typedef int CGSWindow;
  typedef int CGSWorkspace;
  typedef void* CGSValue;

  /* Get the default connection for the current process. */
  extern CGSConnection _CGSDefaultConnection(void);

  /* /MJakubowski/ Get connection for given PSN */
  extern CGError CGSGetConnectionIDForPSN(const CGSConnection connection, ProcessSerialNumber * psn, CGSConnection * targetConnection);

  // Get on-screen window counts and lists.
  extern CGError CGSGetOnScreenWindowCount(const CGSConnection cid, CGSConnection targetCID, int* outCount);
  extern CGError CGSGetOnScreenWindowList(const CGSConnection cid, CGSConnection targetCID, int count, int* list, int* outCount);
  // Position
  extern CGError CGSGetWindowBounds(CGSConnection cid, CGSWindowID wid, CGRect *outBounds);
  extern CGError CGSGetScreenRectForWindow(const CGSConnection cid, CGSWindow wid, CGRect *outRect);

  // Properties
  extern CGError CGSGetWindowProperty(const CGSConnection cid, CGSWindow wid, CGSValue key, CGSValue *outValue);


#ifdef __cplusplus
}
#endif

/* QCFString from Qt */
#include <QString>
template <typename T>
class QCFType
{
public:
    inline QCFType(const T &t = 0) : type(t) {}
    inline QCFType(const QCFType &helper) : type(helper.type) { if (type) CFRetain(type); }
    inline ~QCFType() { if (type) CFRelease(type); }
    inline operator T() { return type; }
    inline QCFType operator =(const QCFType &helper)
    {
        if (helper.type)
            CFRetain(helper.type);
        CFTypeRef type2 = type;
        type = helper.type;
        if (type2)
            CFRelease(type2);
        return *this;
    }
    inline T *operator&() { return &type; }
    static QCFType constructFromGet(const T &t)
    {
        CFRetain(t);
        return QCFType<T>(t);
    }
protected:
    T type;
};

class QCFString : public QCFType<CFStringRef>
{
public:
    inline QCFString(const QString &str) : QCFType<CFStringRef>(0), string(str) {}
    inline QCFString(const CFStringRef cfstr = 0) : QCFType<CFStringRef>(cfstr) {}
    inline QCFString(const QCFType<CFStringRef> &other) : QCFType<CFStringRef>(other) {}
    operator QString() const;
    operator CFStringRef() const;
    static QString toQString(CFStringRef cfstr);
    static CFStringRef toCFStringRef(const QString &str);
private:
    QString string;
};




#endif // QXTWINDOWSYSTEM_MAC_H
