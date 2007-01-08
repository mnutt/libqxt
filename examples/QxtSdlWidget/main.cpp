#include "MySdlWidget.h"

#include <QApplication>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	MySdlWidget sdlWidget;
	sdlWidget.setBackgroundColor(Qt::red);
	sdlWidget.show();

	return app.exec();
}
