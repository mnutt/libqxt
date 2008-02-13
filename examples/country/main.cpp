#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <QxtLanguageComboBox>
#include "testdialog.h"

int main(int argc, char* argv[])
{
//    Q_INIT_RESOURCE(flags);

    QApplication app(argc, argv);

    QTranslator trans;
    bool ok = trans.load(":/qxt_"+QLocale::system().name());
    if (!ok)
      qDebug() << "Loading translation failed.";
    qDebug() << trans.translate("Country", "Germany");

    app.installTranslator(&trans);

    TestDialog* w = new TestDialog();

    w->show();
    app.exec();
} 
