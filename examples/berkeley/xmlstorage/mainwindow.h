#include "ui_mainwindow.h"
#include "model.h"
class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow();
private:
    Ui::MainWindow ui;
    XmlDbModel model;

private slots:
    void on_actionQuit_triggered();
    void on_actionLoad_triggered();
};

