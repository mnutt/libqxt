#include <QObject>

class TestReturnValue : public QObject {
Q_OBJECT
public:
    TestReturnValue(QObject* parent = 0);

    Q_INVOKABLE int addOne(int p);
};
