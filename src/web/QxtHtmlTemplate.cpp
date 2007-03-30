#include "QxtHtmlTemplate.h"
#include <QFile>

QxtHtmlTemplate::QxtHtmlTemplate(QObject* 
parent) : QObject(parent) 
	{
	}


bool QxtHtmlTemplate::open(const QString& filename)
	{
	QFile f(filename);
	f.open(QIODevice::ReadOnly);
	data = f.readAll();
	f.close();
	if (data.isEmpty())return false;
	return true;
	}


void QxtHtmlTemplate::assign(QString key, QString value) 
	{
	vars[key] = value.replace("\\", "\\\\").replace("{", "\\{");
	}

QString QxtHtmlTemplate::evaluate() const 
	{
	QString output = data;
	foreach(QString key, vars.keys()) 
		{
		output = output.replace("<?="+key+"?>", vars[key]);
		}
	return output;
	}
