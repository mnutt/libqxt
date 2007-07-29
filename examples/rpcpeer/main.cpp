#include <QxtApplication>
#include <QxtRPCPeer>
#include <QxtSpanSlider>
#include <QxtSingleInstance>

int main(int argc, char** argv)
	{
	QxtApplication app(argc,argv);
	QxtSpanSlider slider;
	QxtRPCPeer peer;
	peer.setRPCType(QxtRPCPeer::Peer);

	/**QxtSingleInstance is experimental. Do not kill the app, use the guis close button instead*/
	QxtSingleInstance tst("org.libqxt.examples.rpcpeer.singleinstance");
	if(tst.isAlreadyStarted())
		peer.connect ( QHostAddress::LocalHost, 56663);
	else
		peer.listen ( QHostAddress::LocalHost, 56663);

	peer.attachSignal (&slider, SIGNAL(spanChanged(int,int)));
	peer.attachSlot ( "spanChanged",&slider, SLOT(setSpan(int,int))); 

	slider.resize(80,200);
	slider.show();
	app.exec();
	};


#include "main.moc"
