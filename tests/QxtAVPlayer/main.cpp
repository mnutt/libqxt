#include <QApplication>
#include <QxtMedia/QxtAVPlayer>
#include <QStringList>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QxtAVPlayer player;
	player.play(app.arguments()[1]);

	return app.exec();
}
