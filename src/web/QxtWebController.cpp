#include "QxtWebController.h"
#include "QxtWebApplication_p.h"
#include "QxtWebInternal.h"
#include "QxtHtmlTemplate.h"

QxtWebController::QxtWebController(QObject* parent,QString objectName_c):QObject(parent)
	{
	if (!objectName_c.isEmpty())
		setObjectName(objectName_c);

	view=0;
	}

int QxtWebController::index()
	{
	QxtWebInternal::internalPage(404,
		
		"You are seeing this page becouse someone forgot to reimplement the index function of this Controller. (\""+objectName()+"\")<br/>"
		,document(),0,
		"When you inherit from QxtWebController, this is the minimal code: "
		"<small><pre>"		
		+QxtWebInternal::toHtml("#include <QxtWebController>")+"<br/>"
		
		+QxtWebInternal::toHtml("class "+objectName()+"Controller : public  QxtWebController { ")+"<br/>"
		+"Q_OBJECT<br/>"
		+"public:<br/>"
		+"<br/>    "
		+QxtWebInternal::toHtml(objectName()+"Controller(QObject* parent):QxtWebController(parent,\""+objectName()+"\"){}")+"<br/>"
		+"<br/>"
		+QxtWebInternal::toHtml("    int QxtWebController::index()")+"<br/>"
		+QxtWebInternal::toHtml("            {return 0;}")+"<br/>"
		+QxtWebInternal::toHtml("}")+"<br/>"
		+"</pre></small><br/>"


		);


	return -1;
	}


void QxtWebController::push( QHash<QByteArray, QByteArray> server,QHash<QByteArray, QString>  post, QxtHtmlTemplate  *v,QTextStream * s )
	{
	view = v;
	stream=s;
	POST=post;
	SERVER=server;
	}

QTextStream & QxtWebController::document()
	{
	return *stream;
	}

void QxtWebController::assign(QString key, QString value)
	{
	if (!view)
		{
		qWarning("QxtWebController::assign can only be called within a web slot");
		return;
		}
	view->assign(key,value);
	}

