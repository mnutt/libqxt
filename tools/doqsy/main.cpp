#include <QFile>
#include <QDebug>
#include <QtXml>
#include <QxtHtmlTemplate>
#include <QStringList>
#include <QPair>
#include <QHash>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include "parser.h"
#include "output.h"





int main(int argc,char ** argv)
{

    QCoreApplication app(argc,argv);
    qDebug("[greetings]");


    QString settingsfile="Doqsyfile";


    if(app.arguments().count()>1)
    {
       settingsfile=app.arguments().at(1);
    }

    if(!QFileInfo(settingsfile).exists())
        qFatal("cannot open %s",qPrintable(settingsfile));

    if (!QDir::setCurrent (QFileInfo(settingsfile).absolutePath ()))
        qFatal("unable to change working directory to %s",qPrintable(QFileInfo(settingsfile).absolutePath ()));

    QSettings settings(settingsfile,QSettings::IniFormat);
    settings.beginGroup ("doqsy");
    outputDir=settings.value("output","doc").toString();
    templateDir=settings.value("templates","templates").toString();
    QString doxyexe=settings.value("doxygen","doxygen").toString();



    QDir().mkpath(outputDir);
    settings.endGroup();

    qDebug("[cleaning output dir]");
    foreach(QString asdasdasdasd,QDir(outputDir).entryList ())
    {
        QFile(outputDir+QDir::separator()+asdasdasdasd).remove();
    }



    settings.beginGroup ("doxygen");
    Doxygen doxygen(&settings);
    settings.endGroup();


    qDebug("[beginn parsing]");
    doxygen.run();

    qDebug("[copying referenced files]");


    filesIShouldCopy<<"stylesheet.css"<<"logo.png"<<"qxt.qhcp"<<"see.png"<<"note.png"<<"warning.png"<<"implicitshared.png";

    foreach(QString f,filesIShouldCopy)
    {
        QFile(templateDir+QDir::separator ()+f).copy (outputDir+QDir::separator ()+f);
        qDebug()<<f;
    }


    #if QT_VERSION >= 0x040400
    QtAssistantNG assitantng(&settings);
    assitantng.run();
    #endif



    qDebug("[done]");
    return 0;
}

