/*
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

#ifndef QXTSNAPSHOTPREVIEW_H
#define QXTSNAPSHOTPREVIEW_H

#include <QTime>
#include <QFrame>

class QxtSnapshotPreview : public QFrame
{
	Q_OBJECT

public:
	QxtSnapshotPreview(QWidget* parent = 0);
	virtual ~QxtSnapshotPreview();

	QPixmap snapshot() const { return shot; }
	void setSnapshot(const QPixmap& snapshot);

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);

private slots:
	void delayedUpdate();
	void updatePreview();

private:
	QTime time;
	QPoint point;
	QPixmap shot;
	QPixmap preview;
};

#endif // QXTSNAPSHOTPREVIEW_H
