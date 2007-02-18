/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTERROR_H
#define QXTERROR_H

#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

/**
\class QxtError QxtError

\ingroup core

\brief Information about Errors ocuring inside Qxt

might add more features in future.
*/

/*! \relates QxtError
droping an error inside a function that returns QxtError


short for return  QxtError(__FILE__,__LINE__,x);
*/
#define QXT_DROP(x) return QxtError(__FILE__,__LINE__,x);


/*! \relates QxtError
droping no error inside a function that returns QxtError

short for return QxtError(__FILE__,__LINE__,Qxt::NoError);
*/
#define QXT_DROP_OK return QxtError(__FILE__,__LINE__,Qxt::NoError);


/*! \relates QxtError
forward a drop


drops from this function if the call inside dropped too.
the inner function must return or be a QxtError.

example
\code
QXT_DROP_F(critical_function());
\endcode

*/
#define QXT_DROP_F(call) {QxtError error_sds = call; if (error_sds != Qxt::NoError )return error_sds; }



class QXT_CORE_EXPORT QxtError
	{
	public:
		QxtError(char * file, long line, Qxt::ErrorCode errorcode)
			{
			file_m=file;
			line_m=line;
			errorcode_m=errorcode;
			}


		Qxt::ErrorCode errorCode() const
			{return errorcode_m;}

		long line() const
			{return line_m;}

		char * file() const
			{return file_m;}

		operator Qxt::ErrorCode()
			{
			return errorcode_m;
			}


	private:
		Qxt::ErrorCode errorcode_m;
		long line_m;
		char * file_m;
	};


#endif
