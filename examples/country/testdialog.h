#ifndef TESTDIALOG_H_INCLUDED
#define TESTDIALOG_H_INCLUDED

#include <QDebug>
#include "ui_country.h"
#include <QxtCountryModel>



class TestDialog : public QDialog
 {
     Q_OBJECT

 public:
     TestDialog(QWidget *parent = 0)
     : QDialog(parent)
     {
       ui.setupUi(this);
       ui.label->setText(QString("Current Locale: %1").arg(QLocale::system().name()));
       ui.tableView->setModel(new QxtCountryModel(this));
     }

 private:
     Ui::Dialog ui;
 };

#endif // TESTDIALOG_H_INCLUDED
