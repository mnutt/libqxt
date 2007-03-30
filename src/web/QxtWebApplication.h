#ifndef QXTWEBAPPLICATION_HEADER_GIAURX_H
#define QXTWEBAPPLICATION_HEADER_GIAURX_H

#include <QObject>
#include <QxtCore/QxtError>
#include <QxtCore/QxtPimpl>
#include <QHostAddress>

class QxtWebApplicationPrivate;
class QxtWebApplication : public QObject
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtWebApplication);
	public:
		QxtWebApplication(void (*callback)(QObject *),QObject * parent=0);
		QxtError listen(const QHostAddress & address = QHostAddress::Any, quint16 port = 8000);
	};




#endif

