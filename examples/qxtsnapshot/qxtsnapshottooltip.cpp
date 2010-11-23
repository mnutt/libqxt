/*
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

#include "qxtsnapshottooltip.h"
#include "qxtsnapshotpreview.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>

static const QSize MAX_SIZE(250, 250);

QxtSnapshotToolTip::QxtSnapshotToolTip(QxtSnapshotPreview* preview)
	: QWidget(preview), preview(preview)
{
	text = new QLabel(this);
	image = new QLabel(this);
	
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(image, 0, Qt::AlignCenter);
	layout->addWidget(text, 0, Qt::AlignHCenter | Qt::AlignTop);
}

QxtSnapshotToolTip::~QxtSnapshotToolTip()
{
}

void QxtSnapshotToolTip::showEvent(QShowEvent* event)
{
	QPixmap pixmap = preview->snapshot();
	if (!pixmap.isNull())
	{
		QString info("<table>"
				"<tr><td><b>Width:</b></td><td>%1px</td></tr>"
				"<tr><td><b>Height:</b></td><td>%2px</td></tr>"
				"<tr><td><b>Depth:</b></td><td>%3bpp</td></tr>"
				"<tr><td><b>Serial:</b></td><td>%4</td></tr>"
				"</table>");
		text->setText(info.arg(pixmap.width()).arg(pixmap.height())
				.arg(pixmap.depth()).arg(pixmap.serialNumber()));
		
		QSize size = pixmap.size().boundedTo(MAX_SIZE);
		image->setPixmap(pixmap.scaled(size, Qt::KeepAspectRatio));
	}
	else
	{
		image->clear();
		text->setText("N/A");
	}
	
	QWidget::showEvent(event);
}
