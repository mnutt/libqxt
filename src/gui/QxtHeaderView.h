#ifndef QxtHeaderViewHHGuard
#define QxtHeaderViewHHGuard
#include <Qxt/qxtglobal.h>
#include <QHeaderView>


class QPainter;
class QAction;
class QxtHeaderViewPrivate;
class QXT_GUI_EXPORT QxtHeaderView : public QHeaderView
	{
	Q_OBJECT

	public:
		QxtHeaderView (Qt::Orientation orientation ,QWidget * parent);	
		void addAction(QAction * action);
	protected:
		virtual void subPaint(QPainter * painter, const QRect & rect, int logicalIndex,QSize  icon_size, int spacing) const;
		virtual void subClick(QMouseEvent * m,QSize icon_size, int spacing ) ;
                virtual int  subWidth(QSize icon_size, int spacing) const;
	signals:
		void checkBoxChanged(bool);

        private:
		virtual	void paintSection ( QPainter * painter, const QRect & rect, int logicalIndex ) const;
		virtual void mousePressEvent ( QMouseEvent * m );
                virtual void mouseMoveEvent ( QMouseEvent * event );

                QxtHeaderViewPrivate * priv;

	};


#endif
