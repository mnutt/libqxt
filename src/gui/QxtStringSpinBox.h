/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTSTRINGSPINBOX_H
#define QXTSTRINGSPINBOX_H

#include <QSpinBox>
#include <Qxt/qxtglobal.h>
#include <QxtPimpl.h>

class QxtStringSpinBoxPrivate;

class QXT_GUI_EXPORT QxtStringSpinBox : public QSpinBox
{
	Q_OBJECT
	QXT_DECLARE_PRIVATE(QxtStringSpinBox);
	Q_PROPERTY(QStringList strings READ strings WRITE setStrings)
	
public:
	explicit QxtStringSpinBox(QWidget* pParent = 0);
	~QxtStringSpinBox();
	
	const QStringList& strings() const;
	void setStrings(const QStringList& strings);
	
#ifndef QXT_DOXYGEN_RUN
	virtual void fixup(QString& input) const;
	virtual QValidator::State validate(QString& input, int& pos) const;

protected:
	virtual QString textFromValue(int value) const;
	virtual int valueFromText(const QString& text) const;
#endif // QXT_DOXYGEN_RUN
};

#endif // QXTSTRINGSPINBOX_H
