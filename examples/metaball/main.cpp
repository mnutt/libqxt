#include <QApplication>
#include <QxtMetaBall>
#include "test.h"

int main(int argc, char **argv)
        {
        QApplication app (argc,argv);
	A sender;
	B receiver;
	QxtMetaBall::connect(&sender,SIGNAL(signal(int)),&receiver,SLOT(slot(bool)),BALL(value>0));
	sender.test(-99);
        return 0;
        }

