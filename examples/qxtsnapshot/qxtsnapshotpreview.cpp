/*
 *  Copyright (C) 1997-2002 Richard J. Moore
 *  Copyright (C) 2000 Matthias Ettrich
 *  Copyright (C) 2002 Aaron J. Seigo
 *  Copyright (C) 2003 Nadeem Hasan
 *  Copyright (C) 2004 Bernd Brandstetter
 *  Copyright (C) 2006 Urs Wolfer <uwolfer @ fwo.ch>
 *  Copyright (C) 2007 J-P Nurmi
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#include "qxtsnapshotpreview.h"
#include "qxtsnapshottooltip.h"
#include <QStylePainter>
#include <QApplication>
#include <QMouseEvent>
#include <QxtToolTip>
#include <QMimeData>
#include <QTimer>
#include <QDrag>

static const int UPDATE_DELAY = 200;

QxtSnapshotPreview::QxtSnapshotPreview(QWidget* parent)
	: QFrame(parent)
{
	setCursor(Qt::OpenHandCursor);
	QxtToolTip::setToolTip(this, new QxtSnapshotToolTip(this));
}

QxtSnapshotPreview::~QxtSnapshotPreview()
{
}

void QxtSnapshotPreview::setSnapshot(const QPixmap& snapshot)
{
	shot = snapshot;
	updatePreview();
}

void QxtSnapshotPreview::mousePressEvent(QMouseEvent* event)
{
	QFrame::mousePressEvent(event);
	if (event->button() == Qt::LeftButton)
		point = event->pos();
}

void QxtSnapshotPreview::mouseMoveEvent(QMouseEvent* event)
{
	QFrame::mouseMoveEvent(event);
	if (!point.isNull() && !preview.isNull() &&
		(event->pos() - point).manhattanLength() >= QApplication::startDragDistance())
	{
		point = QPoint();

		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData;
		mimeData->setImageData(preview.toImage());
		drag->start();
	}
}

void QxtSnapshotPreview::mouseReleaseEvent(QMouseEvent* event)
{
	QFrame::mouseReleaseEvent(event);
	point = QPoint();
}

void QxtSnapshotPreview::paintEvent(QPaintEvent* event)
{
	QFrame::paintEvent(event);
	QStylePainter painter(this);
	int fw = frameWidth();
	QRect rect = frameRect().adjusted(fw, fw, -fw, -fw);
	painter.drawItemPixmap(rect, Qt::AlignCenter, preview);
}

void QxtSnapshotPreview::resizeEvent(QResizeEvent* event)
{
	QFrame::resizeEvent(event);
	time.start();
	delayedUpdate();
}

void QxtSnapshotPreview::delayedUpdate()
{
	if (time.elapsed() >= UPDATE_DELAY)
		updatePreview();
	else
		QTimer::singleShot(UPDATE_DELAY - time.elapsed(), this, SLOT(delayedUpdate()));
}

void QxtSnapshotPreview::updatePreview()
{
	if (!shot.isNull())
		preview = shot.scaled(width(), height(), Qt::KeepAspectRatio);
	update();
}
