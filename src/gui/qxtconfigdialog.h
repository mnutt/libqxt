/****************************************************************************
**
** Copyright (C) J-P Nurmi <jpnurmi@gmail.com>. Some rights reserved.
**
** This file is part of the QxtGui module of the
** Qt eXTension library <http://libqxt.sourceforge.net>
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef QXTCONFIGDIALOG_H
#define QXTCONFIGDIALOG_H

#include <QDialog>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QListWidget;
class QStackedWidget;
class QDialogButtonBox;
class QxtConfigDialogPrivate;

class QXT_GUI_EXPORT QxtConfigDialog : public QDialog
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtConfigDialog);
	Q_PROPERTY(int count READ count)
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
	Q_PROPERTY(bool hoverEffect READ hasHoverEffect WRITE setHoverEffect)
	Q_PROPERTY(QxtConfigDialog::IconPosition iconPosition READ iconPosition WRITE setIconPosition)
	Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
	Q_ENUMS(IconPosition)

public:
	enum IconPosition { North, West, East };

	explicit QxtConfigDialog(QWidget* parent = 0, Qt::WindowFlags flags = 0);
	explicit QxtConfigDialog(QxtConfigDialog::IconPosition position, QWidget* parent = 0, Qt::WindowFlags flags = 0);
	virtual ~QxtConfigDialog();

	QDialogButtonBox* dialogButtonBox() const;
	void setDialogButtonBox(QDialogButtonBox* buttonBox);
	
	bool hasHoverEffect() const;
	void setHoverEffect(bool enabled);

	QxtConfigDialog::IconPosition iconPosition() const;
	void setIconPosition(QxtConfigDialog::IconPosition position);

	QSize iconSize() const;
	void setIconSize(const QSize& size);

	int addPage(QWidget* page, const QIcon& icon, const QString& title = QString());
	int insertPage(int index, QWidget* page, const QIcon& icon, const QString& title = QString());
	void removePage(int index);

	int count() const;
	int currentIndex() const;
	QWidget* currentPage() const;
	int indexOf(QWidget* page) const;
	QWidget* page(int index) const;

	bool isPageEnabled(int index) const;
	void setPageEnabled(int index, bool enabled);

	bool isPageHidden(int index) const;
	void setPageHidden(int index, bool hidden);

	QIcon pageIcon(int index) const;
	void setPageIcon(int index, const QIcon& icon);

	QString pageTitle(int index) const;
	void setPageTitle(int index, const QString& title);

	QString pageToolTip(int index) const;
	void setPageToolTip(int index, const QString& tooltip);

	QString pageWhatsThis(int index) const;
	void setPageWhatsThis(int index, const QString& whatsthis);

public slots:
	void setCurrentIndex(int index);
	void setCurrentPage(QWidget* page);

signals:
	void currentIndexChanged(int index);

protected:
	QListWidget* listWidget() const;
	QStackedWidget* stackedWidget() const;
};

#endif // QXTCONFIGDIALOG_H
