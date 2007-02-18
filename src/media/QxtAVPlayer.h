/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#include <QObject>
#include <QString>
#include <QDebug>
class QxtAVFile;
class  QxtAVPlayer : public QObject
	{
	Q_OBJECT
	public:
		QxtAVPlayer(QObject * parent =0);
		~QxtAVPlayer();
		bool open(int framesPerBuffer);

		QxtAVFile * currentFile();
		float * scope();

		void up_fetch_eof();


	public slots:
		void play(QxtAVFile * file);
		void play(QString filename);
		void stop();
		void echo(QString e){qDebug()<<e;};
		void setVolume(float v);
	signals:
		void error (QString);
		void currentEof ();
	};


