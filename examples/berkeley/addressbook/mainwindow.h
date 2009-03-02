#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "ui_mainwindow.h"
#include "contact.h"
#include <QxtBdbHash>

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();
private:
    Ui::MainWindow ui;
    QxtBdbHash<QString,Contact>  hash;
    void initTree();
private slots:
    void on_addButton_clicked();
};

#endif // MAINWINDOW_H_INCLUDED
