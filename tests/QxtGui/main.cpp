#include <QApplication>
#include <QxtTreeWidget>

int main (int argc, char ** argv)
	{
	QApplication app(argc,argv);



	QTreeWidget treewidget;
	treewidget.show();



	return app.exec();
	}
