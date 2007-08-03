#include <QtGui>
#include <qxtmetaobject.h>

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
    QxtMetaObject::connect(b, SIGNAL(cursorPositionChanged(int,int)), QxtMetaObject::bind(t, SLOT(display(int)), QXT_BIND(1)));
    QxtMetaObject::connect(b, SIGNAL(cursorPositionChanged(int,int)), QxtMetaObject::bind(t2, SLOT(display(int)), QXT_BIND(2)));
    w.show();
    return app.exec();
}
