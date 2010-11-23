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

#ifndef QXTSNAPSHOT_H
#define QXTSNAPSHOT_H

#include "ui_qxtsnapshot.h"

class QxtSnapshot : public QDialog
{
	Q_OBJECT

public:
	QxtSnapshot(QWidget* parent = 0);
	~QxtSnapshot();

	enum CaptureMode
	{
		FullScreen	= 0,
		Choose		= 1,
		Cursor		= 2,
		Region		= 3
	};

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private slots:
	void on_btnAbout_clicked();
	void on_btnCopy_clicked();
	void on_btnNew_clicked();
	void on_btnSave_clicked();
	void on_btnQuit_clicked();

	void grab();

private:
	WId chooseWindow();
	void delayedGrab();
	void showResult(const QPixmap& pixmap);

	WId chosen;
	QRect region;
	QPoint origin;
	QRubberBand* band;
	Ui::QxtSnapshot ui;
};

#endif // QXTSNAPSHOT_H
