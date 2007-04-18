#ifndef QxtHeaderViewHHGuard
#define QxtHeaderViewHHGuard

#include <QHeaderView>
#include <QxtPimpl>

class QPainter;
class QAction;
class QxtHeaderViewPrivate;
class QXT_GUI_EXPORT QxtHeaderView : public QHeaderView
	{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtHeaderView);

	public:
		QxtHeaderView (Qt::Orientation orientation ,QWidget * parent);	
		void addAction(QAction * );
	protected
		virtual int subPaint(QPainter * painter, const QRect & rect, int logicalIndex,QSize icon_size, int spacing);
	signals:
		void checkBoxChanged(bool);
	};


#endif
