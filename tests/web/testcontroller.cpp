#include "testcontroller.h"



InfoController::InfoController(QObject* parent):QxtWebWidget(parent,"info")
	{
	if (!view.open("app/internal/aframe.html"))qWarning("template load failed");
	view.assign("body","<a href=/info/plopp/>click me</a>");
	view.assign("url","info");

	}





int InfoController::plopp()
	{
	QTimer::singleShot(1000,this,SLOT(sec1()));
	QTimer::singleShot(2000,this,SLOT(sec2()));
	QTimer::singleShot(5000,this,SLOT(sec3()));
	QTimer::singleShot(30000,this,SLOT(sec4()));

	return 0;
	}

int InfoController::index()
	{
	view.assign("body","<a href=/info/plopp/>click me</a>");
	emit(update());
	return 0;
	}
 void InfoController::paintEvent(QTextStream & stream)
	{
	stream<<view.render();
	}


void InfoController::sec1()
	{
	view.assign("body","<a href=/info/plopp/>click me</a><br/><strong>HA!!</strong>");
	emit(update());
	}


void InfoController::sec2()
	{
	view.assign("body","<a href=/info/plopp/>click me</a><br/><strong>This is asyncrounus!!!</strong>");
	emit(update());
	}


void InfoController::sec3()
	{
	view.assign("body","<a href=/info/plopp/>click me</a><br/><strong>seriously, it is.</strong>");
	emit(update());
	}

void InfoController::sec4()
	{
	view.assign("body","<strong>Ok i think you had enough, go and do something usefull.</strong>");
	emit(update());
	}

