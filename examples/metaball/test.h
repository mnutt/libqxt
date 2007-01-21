#include <QDebug>
#include <QObject>
class 	A:public QObject
	{
	Q_OBJECT
	public:
		A():QObject(){}
	

		void test(int a)
			{
			emit(signal(a));
			}

	
	signals:
		void signal(int);	


	};



class 	B:public QObject
	{
	Q_OBJECT
	public:
		B():QObject(){}	


	public slots:
		void slot(bool a)
			{qDebug()<<"slot received"<<a;}	
	
	};

