/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

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
#define fortimes(n) for (QxtHypeValue<typeof(n)> i=0; i<n; i++)



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
	const QxtHyperValue<T>& operator++(int) 
		{
		QxtHyperValue<T> clone = *this;
		value++;
		return clone;
		}
	const QxtHyperValue<T>& operator--(int) 
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
        	T* value;
	};





#endif
