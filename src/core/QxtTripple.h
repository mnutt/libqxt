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
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/
/**
\class QxtTripple QxtTripple

\ingroup core

\brief Template class that stores three values
 
*/

#include <QxtDefines.h>


/*! \relates QxtTripple 
 * returns a QxtTripple with values \a x ,\a y and \a z
 */
#define qMakeTripple(x,y,z)  QxtTripple <typeof(x),typeof(y),typeof(z)>(x,y,z )

template <typename T, typename K,typename L>
class QXT_DLLEXPORT QxtTripple 
	{


	public:
		QxtTripple (T a,K b ,L c)
			{v1=a;v2=b;v3=c;}
	T	v1;
	K	v2;
	L	v3;

	};

