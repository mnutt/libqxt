/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
// Own
#include "qxttabbar.h"
#include "qxttabbar_p.h"

// Qt
#include <QtGui> // TODO remove and insert only the needed headers

class Tab
{

public:
    void save(int index, const QTabBar* const tabbar) {
        if (!tabbar) return;
        m_icon      = tabbar->tabIcon(index);
        m_data      = tabbar->tabData(index);
        m_text      = tabbar->tabText(index);
        m_textColor = tabbar->tabTextColor(index);
        m_toolTip   = tabbar->tabToolTip(index);
        m_whatsThis = tabbar->tabWhatsThis(index);
    }
    void restore(int index, QTabBar* tabbar) const {
        if (!tabbar) return;
        tabbar->setTabIcon(index, m_icon);
        tabbar->setTabData(index, m_data);
        tabbar->setTabText(index, m_text);
        tabbar->setTabTextColor(index, m_textColor);
        tabbar->setTabToolTip(index, m_toolTip);
        tabbar->setTabWhatsThis(index, m_whatsThis);
    }

private:
    QIcon     m_icon;
    QVariant  m_data;
    QString   m_text;
    QColor    m_textColor;
    QString   m_toolTip;
    QString   m_whatsThis;
};

QxtTabBarPrivate::QxtTabBarPrivate() : reorderable(false)
{
}

/*!
    \class QxtTabBar QxtTabBar
    \ingroup QxtGui
    \brief An extended QTabBar.

    QxtTabBar provides tabs that can be reordered. QxtTabWidget internally uses a QxtTabBar and thus is reorderable too.

    Example usage:
    \code
    QxtTabBar* tb = new QxtTabBar;
    tb->setReoderable(true); // Tabs are reorderable now.
    \endcode
 */

/*!
    \fn QxtTabBar::tabReordered(int previousIndex, int newIndex)

    This signal is emitted whenever a tab is moved from \a previousIndex to the new position \a newIndex.
 */

/*!
    Constructs a new QxtTabBar with \a parent.
 */

QxtTabBar::QxtTabBar(QWidget* parent)
        : QTabBar(parent)
{
    QXT_INIT_PRIVATE(QxtTabBar);
    setAcceptDrops(true);
}

QxtTabBar::~QxtTabBar() {}

/*!
    \property QxtTabBar::reorderable
    \brief This property holds whether the tabs are reorderable by drag and drop or not.

    The default value of this property is false. If set to true the signal tabsReodered will be emitted whenever the order changes.

    \sa tabsReordered()
 */

bool QxtTabBar::reorderable() const
{
    return qxt_d().reorderable;
}

void QxtTabBar::setReorderable(bool reorderable)
{
    qxt_d().reorderable = reorderable;
}

/*!
    \reimp
 */
void QxtTabBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        qxt_d().dragStartPos = event->pos();
    QTabBar::mousePressEvent(event);
}

/*!
    \reimp
 */
void QxtTabBar::mouseMoveEvent(QMouseEvent* event)
{
    QTabBar::mouseMoveEvent(event);
    if (!qxt_d().reorderable) return;

    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - qxt_d().dragStartPos).manhattanLength()
        < QApplication::startDragDistance())
        return;

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    // a crude way to distinguish tab-reodering drops from other ones
    mimeData->setData("action", "tab-reordering") ;
    drag->setMimeData(mimeData);
#if (QT_VERSION >= QT_VERSION_CHECK(4, 3, 0))
    drag->exec();
#else
    drag->start();
#endif
}

/*!
    \reimp
 */
void QxtTabBar::dragEnterEvent(QDragEnterEvent* event)
{
    // Only accept if it's an tab-reordering request
    const QMimeData* m = event->mimeData();
    QStringList formats = m->formats();
    if (formats.contains("action") && (m->data("action") == "tab-reordering")) {
        event->acceptProposedAction();
    }
}

/*!
    \reimp
 */
void QxtTabBar::dropEvent(QDropEvent* event)
{
    int previousIndex   = tabAt(qxt_d().dragStartPos);
    int newIndex     = tabAt(event->pos());

    // Store tab data
    Tab tab;
    tab.save(previousIndex, this);

    // If parent is a QTabWidget we can use it to move the tabs and widgets
    QTabWidget* tw = qobject_cast<QTabWidget*>(parent());

    if (tw) {
        QWidget* w = tw->widget(previousIndex);
        tw->removeTab(previousIndex);
        tw->insertTab(newIndex, w, "");
        tw->setCurrentIndex(newIndex);
    }
    // Tabbar is standalone (not embedded into a QTabWidget)
    else {
        removeTab(previousIndex);
        insertTab(newIndex, "");
        setCurrentIndex(newIndex);
    }

    // Restore tab
    tab.restore(newIndex, this);

    // Inform interested parties about reordering
    if (previousIndex != newIndex) {
        emit tabReordered(previousIndex, newIndex);
    }

    event->acceptProposedAction();
}
