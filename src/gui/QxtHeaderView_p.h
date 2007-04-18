#ifndef QxtHeaderViewPrivateHHGuard
#define QxtHeaderViewPrivateHHGuard


#include <QHeaderView>
#include <QList>

#include "QxtHeaderView.h"


class QPainter;
class QAction;
class QSize;
class QxtHeaderViewPrivate : public QxtPrivate<QHeaderView>
	{
	Q_OBJECT
	QXT_DECLARE_PUBLIC(QxtHeaderView);

	public:
		void construct();
		void addAction(QAction * );


	private:

		virtual	void paintSection ( QPainter * painter, const QRect & rect, int logicalIndex ) const;
		virtual void mousePressEvent ( QMouseEvent * m );

		QList<QAction *> actions;
		QSize * action_size;

	signals:
		void checkBoxChanged(bool);

	};


#endif
