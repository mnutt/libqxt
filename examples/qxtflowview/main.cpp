#include <QApplication>

#include "fsimagemodel.h"
#include <QTreeView>
#include <QxtFlowView>


int main( int argc, char ** argv )
{
    QApplication app ( argc, argv );

    if(app.arguments().count()<2)
       qFatal("./qxtflowview /path/to/images");

    FsImageModel model(app.arguments().at(1));

//     QTreeView view;
//     view.setModel(&model);
//     view.show();


    QxtFlowView w;
    w.setSlideSize(QSize( 4*60,3*60));
    w.resize(800, 600);
    w.setModel(&model);
    w.show();

    return app.exec();
}
