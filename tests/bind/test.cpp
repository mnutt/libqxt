#include <QtGui>
#include <qxtmetaobject.h>
#include <qxtboundfunction.h>
#include "test.h"

TestReturnValue::TestReturnValue(QObject* parent) : QObject(parent) {
}

int TestReturnValue::addOne(int p) {
    return p + 1;
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QWidget w;
    QVBoxLayout* l = new QVBoxLayout(&w);
    QLineEdit* b = new QLineEdit(&w);
    QLCDNumber* t = new QLCDNumber(&w);
    QLCDNumber* t2 = new QLCDNumber(&w);
    l->addWidget(b);
    l->addWidget(t);
    l->addWidget(t2);
    //QxtBoundFunction* fn = QxtMetaObject::bind(t2, SLOT(display(int)), QXT_BIND(2));
    QxtMetaObject::connect(b, SIGNAL(cursorPositionChanged(int,int)), QxtMetaObject::bind(t, SLOT(display(int)), QXT_BIND(1)));
    QxtMetaObject::connect(b, SIGNAL(cursorPositionChanged(int,int)), QxtMetaObject::bind(t2, SLOT(display(int)), QXT_BIND(2)));
    //QxtMetaObject::connect(b, SIGNAL(cursorPositionChanged(int,int)), fn);
    //fn->invoke(Qt::QueuedConnection, 55, 88);

    TestReturnValue v;
    QxtBoundFunction* z = QxtMetaObject::bind(&v, "addOne(int)", Q_ARG(int, 5));
    QxtNullable<int> rv = z->invoke<int>();
    if(!rv.isNull()) t->display(rv);

    w.show();
    return app.exec();
}
