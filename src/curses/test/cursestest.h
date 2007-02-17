#include <QObject>

class Test : public QObject {
Q_OBJECT
public slots:
    void moveWindows();
};
