#ifndef QxtDaemon_HEADER_GUARD
#define QxtDaemon_HEADER_GUARD

#include <QObject>
#include <QString>
#include <QCoreApplication>


class QFile;
class QxtDaemon : public QObject
{
Q_OBJECT
public:
    QxtDaemon(QString applicationName=QCoreApplication::applicationName());
    bool daemonize(bool pidfile=true);
    static int pid();
    bool changeUser(QString name);

    #ifndef QXT_DOXYGEN_RUN

        static void messageHandler(QtMsgType type, const char *msg);
        #ifdef Q_OS_UNIX
            static void signalHandler (int signal);
        #endif

    #endif

private:
    QString m_name;
    QFile *logfile;
Q_SIGNALS:
    void signal(int);
    void hangup();
    void terminate();
};


#endif


