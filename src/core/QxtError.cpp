/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/
#include "QxtError.h"

QxtError::QxtError(char * file, long line, Qxt::ErrorCode errorcode,char * errorString)
{
    file_m=file;
    line_m=line;
    errorcode_m=errorcode;
    errorString_m=errorString;
}


Qxt::ErrorCode QxtError::errorCode() const
{ return errorcode_m; }

long QxtError::line() const
{ return line_m; }

char * QxtError::file() const
{ return file_m; }

QxtError::operator Qxt::ErrorCode()
{ return errorcode_m; }
/*!
The Error String or NULL
depending how the error was constructed. 
Be carefull with stack and temporary objects, QxtError just saves the pointer you passed, not the actual data.
*/
char * QxtError::errorString() const
{ return errorString_m; }


