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


class QXT_CORE_EXPORT QxtError
	{
	public:
		QxtError(char * file, long line, Qxt::QxtError errorcode)
			{
			file_m=file;
			line_m=line;
			errorcode_m=errorcode;
			}


		Qxt::QxtError errorCode() const
			{return errorcode_m;}

		long line() const
			{return line_m;}

		char * file() const
			{return file_m;}

	private:
		Qxt::QxtError errorcode_m;
		long line_m;
		char * file_m;
	};


#endif
