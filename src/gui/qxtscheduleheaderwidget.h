#ifndef QXTSCHEDULEHEADERVIEW_H_INCLUDED
#define QXTSCHEDULEHEADERVIEW_H_INCLUDED

#include <QHeaderView>
#include "qxtglobal.h"

class QxtScheduleView;
class QxtScheduleViewHeaderModel;

class QXT_GUI_EXPORT QxtScheduleHeaderWidget : public QHeaderView
{
    Q_OBJECT

public:
    QxtScheduleHeaderWidget(Qt::Orientation orientation, QxtScheduleView *parent = 0);

protected:
    virtual void            paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const;

private:
    virtual void            setModel(QxtScheduleViewHeaderModel *model);
};

#endif
