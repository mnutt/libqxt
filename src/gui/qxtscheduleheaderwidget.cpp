#include "qxtscheduleheaderwidget.h"
#include "qxtscheduleview.h"
#include "qxtscheduleviewheadermodel_p.h"

#include <QPainter>
#include <QDateTime>
#include <QDate>
#include <QTime>


/**
 *  @internal the QxtAgendaHeaderWidget operates on a internal model , that uses the QxtScheduleView as DataSource
 *
 */

QxtScheduleHeaderWidget::QxtScheduleHeaderWidget(Qt::Orientation orientation , QxtScheduleView *parent) : QHeaderView(orientation, parent)
{
    QxtScheduleViewHeaderModel *model = new QxtScheduleViewHeaderModel(this);
    setModel(model);

    if (parent)
    {
        model->setDataSource(parent);
    }
}

void QxtScheduleHeaderWidget::paintSection(QPainter * painter, const QRect & rect, int logicalIndex) const
{
    if (model())
    {
        switch (orientation())
        {
        case Qt::Horizontal:
        {
            QHeaderView::paintSection(painter, rect, logicalIndex);
        }
        break;
        case Qt::Vertical:
        {
            QTime time = model()->headerData(logicalIndex, Qt::Vertical, Qt::DisplayRole).toTime();
            if (time.isValid())
            {
                QRect temp = rect;
                temp.adjust(1, 1, -1, -1);

                painter->fillRect(rect, this->palette().background());

                if (time.minute() == 0)
                {
                    painter->drawLine(temp.topLeft() + QPoint(temp.width() / 3, 0), temp.topRight());
                    painter->drawText(temp, Qt::AlignTop | Qt::AlignRight, time.toString("hh:mm"));
                }
            }
        }
        break;
        default:
            Q_ASSERT(false); //this will never happen... normally
        }
    }
}

void QxtScheduleHeaderWidget::setModel(QxtScheduleViewHeaderModel *model)
{
    QHeaderView::setModel(model);
}
