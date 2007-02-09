/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/
#include <QObject>
#include <QString>
#include <Qxt/qxtglobal.h>

class QxtAVFile;
class QXT_MEDIA_EXPORT QxtAVPlayer : public QObject
	{
	Q_OBJECT
	public:
		QxtAVPlayer(QObject * parent =0);
		~QxtAVPlayer();
		bool open(int framesPerBuffer);

		QxtAVFile * currentFile();
		float * scope();

	public slots:
		void play(QxtAVFile * file);
		void play(QString filename);
		void stop();
	signals:
		void error (QString);
	};


