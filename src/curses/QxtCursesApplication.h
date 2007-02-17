#ifndef QXTCURSESAPPLICATION_H
#define QXTCURSESAPPLICATION_H

#include <QtCore/QCoreApplication>
#include <QxtCore/QxtPimpl>

class QTimerEvent;
class QxtCursesApplicationPrivate;
class QxtCursesApplication : public QCoreApplication {
Q_OBJECT
public:
    QxtCursesApplication(int& argc, char** argv);
    ~QxtCursesApplication();

    static QObject* focusWidget();
    inline static QxtCursesApplication* instance() { return static_cast<QxtCursesApplication*>(QCoreApplication::instance()); }

private:
    QXT_DECLARE_PRIVATE(QxtCursesApplication);
};

#endif
