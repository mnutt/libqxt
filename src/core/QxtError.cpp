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


