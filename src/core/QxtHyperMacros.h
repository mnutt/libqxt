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

/**
\class QxtHyperMacros QxtHyperMacros

\ingroup core

\brief some helper macros for your daily work

hypermacros use templates in order to work
*/




#ifndef HEADER_GUARDS_QxtHyperMacros_H
#define HEADER_GUARDS_QxtHyperMacros_H


/*! \relates QxtHyperMacros
 * just do something n times
 */
#define fortimes(n) for (QxtHyperValue<typeof(n)> i=0; i<n; i++)



template<typename T>
class QXT_CORE_EXPORT QxtHyperValue
	{
	public:

	QxtHyperValue(const T& p)
		{
		value=p;
		}

	QxtHyperValue<T> & operator=(const QxtHyperValue<T> &rhs)
		{
		value=rhs;
		return this;
		}

	operator T() const
		{
		return value;
		}

	const QxtHyperValue<T>& operator++() 
		{
		value++;
		return this;
		}
	const QxtHyperValue<T>& operator--() 
		{
		value--;
		return this;
		}
	const QxtHyperValue<T> operator++(int) 
		{
		QxtHyperValue<T> clone = *this;
		value++;
		return clone;
		}
	const QxtHyperValue<T> operator--(int) 
		{
		QxtHyperValue<T> clone = *this;
		value--;
		return clone;
		}

       	bool operator== ( T& v)
		{
		return (value==v);
		}

       	bool operator> ( T& v)
		{
		return (value>v);
		}

       	bool operator< ( T& v)
		{
		return (value<v);
		}

    	private:
        	T value;
	};





#endif
