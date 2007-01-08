/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Adam Higerd and Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

/**
\class QxtNullable QxtNullable

\ingroup core

\brief distinct null value compatible with any data type.




in general it's a templated abstraction to allow any data type to be expressed with a null value distinct from any real value.

you can use it for skipable arguments. 
\n 
prepare a function for argument skipping:


\code
void  somefunction( qxtNull(int,a) , qxtNull(int,b) )
{
 
if (!a.isNull())
	{
	int i = a.value();
	//do something with i
	}
 if (!b.isNull())
	{
	int x = b.value();
	//do something with x
	}
}
\endcode



usage:
\code

somefunction(SKIP,1,2);
somefunction(3,4);
somefunction(3,SKIP,6);
somefunction(1);
\endcode

*/




#ifndef QXTNULLABLE_H
#define QXTNULLABLE_H
#include <QxtDefines.h>




/*! \relates QxtNullable
 * defines a skipable argument with type \a t and variable name \a n  
 */
#define qxtNull(t,n)	  QxtNullable<t> n = QxtNullable<t>()








#include <QxtNull.h>





template<typename T>
class QXT_DLLEXPORT QxtNullable {
    public:

        QxtNullable(QxNullableNull);

        QxtNullable(const T& p);

        QxtNullable();
	
	///determinates if the Value is set to something meaningfull
        bool isNull() const;

	///delete Value
	void nullify();

        T& value() const;

        operator T() const;


	void operator=(const T& p);
    private:
        T* val;
};

template<typename T>
QxtNullable<T>::QxtNullable(QxNullableNull) {
    val = 0;
}

template<typename T>
QxtNullable<T>::QxtNullable(const T& p) {
val = const_cast<T*>(&p);
}

template<typename T>
QxtNullable<T>::QxtNullable() {
    val = 0;
}

template<typename T>
QxtNullable<T>::operator T() const {
    return *val;
}

template<typename T>
T& QxtNullable<T>::value() const {
    return *val;
}

template<typename T>
bool QxtNullable<T>::isNull() const {
    return (val==0);
}

template<typename T>
void QxtNullable<T>::nullify() 
	{
	val=0;
	}

template<typename T>

void QxtNullable<T>::operator=(const T& p) 
	{
	val = const_cast<T*>(&p);
	}


#endif