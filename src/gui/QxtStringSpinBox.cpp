/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#include "QxtStringSpinBox.h"

class QxtStringSpinBoxPrivate : public QxtPrivate<QxtStringSpinBox>
{
public:
	QXT_DECLARE_PUBLIC(QxtStringSpinBox);
	int startsWith(const QString& start, QString& string) const;
	QStringList strings;
};

int QxtStringSpinBoxPrivate::startsWith(const QString& start, QString& string) const
{
	const int size = strings.size();
	for (int i = 0; i < size; ++i)
	{
		if (strings.at(i).startsWith(start, Qt::CaseInsensitive))
		{
			// found
			string = strings.at(i);
			return i;
		}
	}
	// not found
	return -1;
}

/*!
    \class QxtStringSpinBox QxtStringSpinBox
    \ingroup gui
    \brief A spin box with string items.

    QxtStringSpinBox is spin box that takes strings. QxtStringSpinBox allows 
    the user to choose a value by clicking the up and down buttons or by 
    pressing Up or Down on the keyboard to increase or decrease the value 
    currently displayed. The user can also type the value in manually.
 */

/*!
    Constructs a new QxtStringSpinBox with \a parent.
 */
QxtStringSpinBox::QxtStringSpinBox(QWidget* pParent) : QSpinBox(pParent)
{
	setRange(0, 0);
}

/*!
    Destructs the spin box.
 */
QxtStringSpinBox::~QxtStringSpinBox()
{
}

/*!
    \property QxtStringSpinBox::strings
    \brief This property holds the string items of the spin box.
 */
const QStringList& QxtStringSpinBox::strings() const
{
	return qxt_d().strings;
}

void QxtStringSpinBox::setStrings(const QStringList& strings)
{
	qxt_d().strings = strings;
	setRange(0, strings.size() - 1);
}

void QxtStringSpinBox::fixup(QString& input) const
{
	// just attempt to change the input string to be valid according to the string list
	// no need to result in a valid string, callers of this function are responsible to
	// re-test the validity afterwards
	
	// try finding a string from the list which starts with input
	input = input.simplified();
	if (!input.isEmpty())
	{
		qxt_d().startsWith(input, input);
	}
}

QValidator::State QxtStringSpinBox::validate(QString& input, int& pos) const
{
	// Invalid:		input is invalid according to the string list
	// Intermediate:	it is likely that a little more editing will make the input acceptable
	//			(e.g. the user types "A" and stringlist contains "ABC")
	// Acceptable:		the input is valid.
	Q_UNUSED(pos);
	QString temp;
	QValidator::State state = QValidator::Invalid;
	if (qxt_d().strings.contains(input))
	{
		// exact match
		state = QValidator::Acceptable;
	}
	else if (input.isEmpty() || qxt_d().startsWith(input, temp) != -1)
	{
		// still empty or some string in the list starts with input
		state = QValidator::Intermediate;
	}
	// else invalid
	return state;
}

QString QxtStringSpinBox::textFromValue(int value) const
{
	Q_ASSERT(qxt_d().strings.isEmpty() || (value >= 0 && value < qxt_d().strings.size()));
	return qxt_d().strings.isEmpty() ? QLatin1String("") : qxt_d().strings.at(value);
}

int QxtStringSpinBox::valueFromText(const QString& text) const
{
	return qxt_d().strings.indexOf(text);
}
