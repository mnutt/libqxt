/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

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

