#include "testcontroller.h"



InfoController::InfoController(QObject* parent):QxtWebWidget(parent,"info")
	{
	if (!view.open("app/internal/aframe.html"))qWarning("template load failed");
	view.assign("body","<a href=/info/plopp/>click me</a>");

	}


int InfoController::plopp()
	{
	QTimer::singleShot(1000,this,SLOT(sec1()));
	QTimer::singleShot(2000,this,SLOT(sec2()));
	QTimer::singleShot(5000,this,SLOT(sec3()));
	return 0;
	}


 void InfoController::paintEvent(QTextStream & stream)
	{
	stream<<"Status: 200  OK\r\n";
	stream<<"Content-Type: text/html\r\n\r\n\r\n";
	stream<<view.render();
	}


void InfoController::sec1()
	{
	view.assign("body","<strong>ZOMG!!!!</strong>");
	emit(update());
	}


void InfoController::sec2()
	{
	view.assign("body","<strong>This is AAAAASYNC!!!</strong>");
	emit(update());
	}


void InfoController::sec3()
	{
	view.assign("body","<strong>seriously, it is!</strong>");
	emit(update());
	}
