#include "hello.h"

HelloWorld::HelloWorld():QxtWebController("root")
{

}

int HelloWorld::index()
{
    echo()<<"<h1>Hello world</h1>";
    return 0;
};




