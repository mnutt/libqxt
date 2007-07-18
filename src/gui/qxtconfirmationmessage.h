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
#ifndef QXTCONFIRMATIONMESSAGE_H
#define QXTCONFIRMATIONMESSAGE_H

#include <QSettings>
#include <QMessageBox>
#include "qxtglobal.h"
#include "qxtpimpl.h"

class QxtConfirmationMessagePrivate;

class QXT_GUI_EXPORT QxtConfirmationMessage : public QMessageBox
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtConfirmationMessage);
	Q_PROPERTY(QString confirmationText READ confirmationText WRITE setConfirmationText);
	
public:
	explicit QxtConfirmationMessage(QWidget* parent = 0);
	virtual ~QxtConfirmationMessage();
	
#if QT_VERSION >= 0x040200
	QxtConfirmationMessage(QMessageBox::Icon icon,
		const QString& title, const QString& text, const QString& confirmation = QString(),
		QMessageBox::StandardButtons buttons = QMessageBox::NoButton, QWidget* parent = 0,
		Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

	static QMessageBox::StandardButton confirm(QWidget* parent,
		const QString& title, const QString& text, const QString& confirmation = QString(),
		QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
		QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
#endif
	
	QString confirmationText() const;
	void setConfirmationText(const QString& confirmation);
	
	static QSettings::Scope settingsScope();
	static void setSettingsScope(QSettings::Scope scope);
	
	static QString settingsPath();
	static void setSettingsPath(const QString& path);
	
	static void reset(const QString& title, const QString& text, const QString& informativeText = QString());
	
public slots:
	int exec();
	void reset();
#ifndef QXT_DOXYGEN_RUN
	virtual void done(int result);
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTCONFIRMATIONMESSAGE_H
