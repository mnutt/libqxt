#include <QCoreApplication>

class QTimerEvent;
class QxtCursesApplication : public QCoreApplication {
Q_OBJECT
public:
    QxtCursesApplication(int& argc, char** argv);
    ~QxtCursesApplication();

    static QObject* focusWidget();

protected:
    void timerEvent(QTimerEvent* event);

    QObject* currentFocus;
};
