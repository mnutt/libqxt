#include <QApplication>
#include "mainwindow.h"
#include "contact.h"

int main(int argc, char ** argv)
{
    QApplication app(argc,argv);

    qRegisterMetaType <Contact> ("Contact");
    qRegisterMetaTypeStreamOperators <Contact> ("Contact");

    MainWindow m;
    m.show();
    app.exec();
}



