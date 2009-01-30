#ifndef QXTSCHEDULEVIEWTEST_H
#define QXTSCHEDULEVIEWTEST_H

#include <QtGui/QMainWindow>
#include "ui_qxtscheduleviewtest.h"

class QxtScheduleViewTest : public QMainWindow
{
    Q_OBJECT

public:
    QxtScheduleViewTest(QWidget *parent = 0);
    ~QxtScheduleViewTest();

private:
    Ui::QxtScheduleViewTestClass ui;
};

#endif // QXTSCHEDULEVIEWTEST_H
