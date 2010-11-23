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

#include "qxtsnapshot.h"
#include <QxtWindowSystem>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QImageWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QClipboard>
#include <QTimer>

QxtSnapshot::QxtSnapshot(QWidget* parent)
	: QDialog(parent), chosen(0), band(0)
{
	ui.setupUi(this);
}

QxtSnapshot::~QxtSnapshot()
{
}

void QxtSnapshot::mousePressEvent(QMouseEvent* event)
{
	QDialog::mousePressEvent(event);

	switch (ui.comboMode->currentIndex())
	{
	case Cursor:
		if (chosen == (WId) -1)
		{
			chosen = QxtWindowSystem::windowAt(event->globalPos());
			setCursor(Qt::ArrowCursor);
			releaseMouse();
			delayedGrab();
		}
		break;
	case Region:
		if (band)
		{
			origin = event->globalPos();
			band->setGeometry(QRect(origin, QSize()));
			band->show();
		}
		break;
	default:
		// nothing to do
		break;
	}
}

void QxtSnapshot::mouseMoveEvent(QMouseEvent* event)
{
	QDialog::mouseMoveEvent(event);

	if (band)
		band->setGeometry(QRect(origin, event->globalPos()).normalized());
}

void QxtSnapshot::mouseReleaseEvent(QMouseEvent* event)
{
	QDialog::mouseReleaseEvent(event);

	if (band)
	{
		region = QRect(band->pos(), band->size());
		delete band;
		band = 0;
		setCursor(Qt::ArrowCursor);
		releaseMouse();
		delayedGrab();
	}
}

void QxtSnapshot::on_btnAbout_clicked()
{
	QMessageBox::information(this, tr("About QxtSnapshot"),
		tr("<h3>About QxtSnapshot</h3>"
		"<p>(c) 2007 J-P Nurmi</p>"
		"<p>This demonstration is intended to highlight the capabilities of "
		"<b>QxtWindowSystem</b> and <b>QxtToolTip</b>. "
		"<b>QxtSnapshot</b> is part of <b>Qxt, the Qt eXTension library</b> &lt;"
		"<a href=\"http://libqxt.sf.net\">http://libqxt.sf.net</a>&gt;.</p>"

		"<p><b>QxtSnapshot</b> is a port of <b>KSnapshot</b> &lt;"
		"<a href=\"http://www.kde.org\">http://www.kde.org</a>&gt;<br/>"
		"(c) 1997-2004, Richard J. Moore,<br/>"
		"(c) 2000, Matthias Ettrich,<br/>"
		"(c) 2002-2003 Aaron J. Seigo,<br>"
		"(c) 2003 Nadeem Hasan,<br>"
		"(c) 2004 Bernd Brandstetter,<br>"
		"(c) 2006 Urs Wolfer.</p>"));
}

void QxtSnapshot::on_btnCopy_clicked()
{
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setPixmap(ui.preview->snapshot());
}

void QxtSnapshot::on_btnNew_clicked()
{
	switch (ui.comboMode->currentIndex())
	{
	case Choose:
		chosen = chooseWindow();
		// flow through
	case FullScreen:
		delayedGrab();
		break;
	case Cursor:
		chosen = (WId) -1;
		setCursor(Qt::CrossCursor);
		grabMouse();
		break;
	case Region:
		band = new QRubberBand(QRubberBand::Rectangle);
		setCursor(Qt::CrossCursor);
		grabMouse();
		break;
	}
}

static QString imageFormats()
{
	QStringList formats;
	QList<QByteArray> tmp = QImageWriter::supportedImageFormats();
	foreach (const QByteArray& format, tmp)
		formats += "*." + format;
	return formats.join(" ");
}

void QxtSnapshot::on_btnSave_clicked()
{
	static QString filter = tr("Images(%1)").arg(imageFormats());
	static QString dir = QCoreApplication::applicationDirPath();
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As - QxtSnapshot"), dir, filter);
	if (!fileName.isNull())
	{
		ui.preview->snapshot().save(fileName);
		dir = QFileInfo(fileName).path();
	}
}

void QxtSnapshot::on_btnQuit_clicked()
{
	close();
	qApp->quit();
}

void QxtSnapshot::grab()
{
	QPixmap pixmap;
	QApplication::beep();
	switch (ui.comboMode->currentIndex())
	{
	case FullScreen:
		pixmap = QPixmap::grabWindow(qApp->desktop()->winId());
		break;
	case Choose:
		if (chosen != (WId) -1)
			pixmap = QPixmap::grabWindow(chosen);
		break;
	case Cursor:
		pixmap = QPixmap::grabWindow(chosen);
		break;
	case Region:
		pixmap = QPixmap::grabWindow(qApp->desktop()->winId(), region.x(), region.y(), region.width(), region.height());
		break;
	default:
		break;
	}
	showResult(pixmap);
}

WId QxtSnapshot::chooseWindow()
{
	WindowList windows = QxtWindowSystem::windows();
	QStringList titles = QxtWindowSystem::windowTitles();
	bool ok = false;
	QString title = QInputDialog::getItem(this, tr("Choose Window - QxtSnapshot"), tr("Choose Window:"), titles, 0, false, &ok);
	if (ok)
	{
		int index = titles.indexOf(title);
		if (index != -1)
			return windows.at(index);
	}
	return (WId) -1;
}

void QxtSnapshot::delayedGrab()
{
	int delay = ui.spinDelay->value();
	QTimer::singleShot(delay * 1000, this, SLOT(grab()));
	if (delay > 0)
		hide();
}

void QxtSnapshot::showResult(const QPixmap& pixmap)
{
	ui.preview->setSnapshot(pixmap);
	ui.btnSave->setEnabled(!pixmap.isNull());
	ui.btnCopy->setEnabled(!pixmap.isNull());
	show();
}
