/*******************************************************************
Qt extended Library 
Copyright (C) 2007 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

/**
\class QxtTrippleList QxtTrippleList

\ingroup kit

\brief Searchable List of Tripples
 
Tripple list provides a list with three values, similar to QxtPairList

\code
QxtTrippleList<int,int,double> list;

list.append(1,2,4.432);
list.append(1,5,3.1233);
list.append(5,6,8.34444);

qDebug()<< list.find(1);                //  (0,1)
qDebug()<< list.find(SKIP,SKIP,4.32);    //  (0)
qDebug()<< list.find(5);                 //  (2)
qDebug()<< list.find(SKIP,2,4,SKIP);     //  (0)

\endcode
you may allso mess around with the list itself

\code
list.list.append(qMakeTripple(1,2,3.2));
\endcode


*/




#include <QList>
#include <QxtTripple>
#include <QxtNullable>
#include <QxtShiftRegister>
#include <QxtDefines.h>

template <typename T, typename K,typename L>
class QXT_KIT_EXPORT QxtTrippleList 
	{


	public:


		QxtTrippleList() {}



		QxtTrippleList( const QxtTrippleList<T,K,L> & other )
			{
			list=other.list;
			}



		QxtTrippleList operator= ( const QxtTrippleList<T,K,L> & other )
			{
			list=other.list;
			}



		void append(T v1, K v2,L v3)
			{
			list.append(qMakeTripple(v1,v2,v3));
			}


		/** \brief search entrys position by match 

		all arguments are optional, due to the use of QxNullable
		
		\code
		find(SKIP,v2);
		find(v1,SKIP,SKIP);
		find(SKIP,SKIP,v3);
		\endcode
		are all valid
		\n
		note that skipping all arguments returns all entrys
		*/ 
		QList<int> find( qxNull(T,v1) , qxNull(K,v2), qxNull(L,v3) )
			{
			QList<int> found;
			
  			for(int i=0;i<list.count();i++)


 				if (
				(v1.isNull() or (list[i].v1==v1))  and
				(v2.isNull() or (list[i].v2==v2))  and
				(v3.isNull() or (list[i].v3==v3))  )
 					found.append(i);
 				



  			return found;
  			}



		///remove an entrys by position
		void remove(int nr)
			{
			list.removeAt(nr);
			}

		///remove a list of entrys by position
		void remove(QList<int> nrs)
			{
			int i;
			foreach (i,nrs)
				list.removeAt(i);
			}




		QList<QxtTripple<T,K,L> > list;
	};
