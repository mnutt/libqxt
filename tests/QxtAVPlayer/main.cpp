#include <QApplication>
#include <QxtMedia/QxtAVPlayer>
#include <QStringList>
#include <QxtSignalWaiter>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QxtAVPlayer player;
	player.play(app.arguments()[1]);



	return	QxtSignalWaiter::wait(&player, SIGNAL(eof()));
}
