#ifndef QXTHTMLTEMPLATE_H
#define QXTHTMLTEMPLATE_H

#include <QObject>
#include <QString>
#include <QHash>

class QxtHtmlTemplate : public QObject 
	{
	Q_OBJECT
	public:
		QxtHtmlTemplate( QObject* parent = 0);
		bool open(const QString& filename);
		void assign(QString key, QString value);
		QString evaluate() const;

	private:
		QString data;
		QHash<QString, QString> vars;
	};

#endif

