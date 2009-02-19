#ifndef HELLO_H_INCLUDED
#define HELLO_H_INCLUDED

#include <QxtWebController>

class HelloWorld : public QxtWebController
{
Q_OBJECT
public:
    HelloWorld();
public slots:
    int index();
};


#endif // HELLO_H_INCLUDED
