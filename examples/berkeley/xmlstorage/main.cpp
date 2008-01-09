#include <QApplication>
#include "mainwindow.h"
#include "node.h"

int main(int argc, char ** argv)
{
    QApplication app(argc,argv);

    qRegisterMetaType <XmlNode> ("XmlNode");
    qRegisterMetaTypeStreamOperators <XmlNode> ("XmlNode");

    MainWindow m;
    m.show();
    app.exec();
}



