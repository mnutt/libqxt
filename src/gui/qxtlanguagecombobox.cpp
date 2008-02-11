/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtDesigner module of the Qt eXTension library
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

#include "qxtlanguagecombobox.h"
#include "qxtlanguagecombobox_p.h"
#include <QtGui>

class Language;
typedef QList<Language> LanguageList;


static QStringList findQmFiles(const QString& pathToTranslations = ":/translations")
{
  QDir dir(pathToTranslations);
  QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files, QDir::Name);

  QMutableStringListIterator i(fileNames);
  while (i.hasNext())
  {
    i.next();
    int start = i.value().indexOf('_');
    int end = i.value().lastIndexOf('.');
    QString s = i.value().mid(start+1, end-start-1).toLower();

    i.setValue(s);
  }

  return fileNames;
}


class Language
{
public:
  Language(const QLocale::Language& language)
  : _mLanguage(language)
  , _mCountryCode("C")
  {
    QLocale loc(language);
    if (loc.language() == language)
      _mCountryCode = loc.name().right(2);
    else
      _mCountryCode = "";

    _mDisplayName = qApp->translate("QLocale", qPrintable(QLocale::languageToString(_mLanguage)));
//    qDebug() << _mDisplayName << _mCountryCode << loc.name();
  };

  bool operator<(const Language& lang) const
  {
    return _mDisplayName < lang._mDisplayName;
  }

  static const LanguageList& getAllLanguages()
  {
    if (_smAllLanguages.empty())
    {

      for (int idx = 0; idx < QLocale::LastLanguage; ++idx)
      {
        QLocale::Language l = static_cast<QLocale::Language>(idx);
        if (l == QLocale::LastLanguage)
          continue;
        // obsolete - NorwegianNynorsk is used instead
        if (l == QLocale::Nynorsk)
          continue;

        _smAllLanguages.push_back(Language(l));
      }

      qSort(_smAllLanguages);
    }
    return _smAllLanguages;
  };

  static const LanguageList& getTrLanguages()
  {
    if (_smTrLanguages.empty())
    {
      QStringList qms = findQmFiles();
      for (int i = 0; i < qms.size(); ++i)
      {
        QLocale locale(qms[i]);
        if (locale.language() == QLocale::C)
          continue;
        _smTrLanguages.push_back(Language(locale.language()));
      }
      qSort(_smTrLanguages);
    }
    return _smTrLanguages;
  };

  const QString& name() const
  { return _mDisplayName; }
  const QLocale::Language& language() const
  { return _mLanguage; }
  const QString& countryName() const
  { return _mCountryCode; }

private:
  QLocale::Language _mLanguage;
  QString _mDisplayName;
  QString _mCountryCode;

  static LanguageList _smAllLanguages;
  static LanguageList _smTrLanguages;
};

LanguageList Language::_smAllLanguages;
LanguageList Language::_smTrLanguages;

class LanguageModel : public QAbstractTableModel
{
  public:
    LanguageModel(const LanguageList& languages, QObject* parent = 0)
    : QAbstractTableModel(parent), _mLanguages(languages)
    {
    }

    int rowCount(const QModelIndex&) const
    {
        return _mLanguages.size();
    }

    int columnCount(const QModelIndex&) const
    {
        return 2;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const
    {
        if (!index.isValid())
            return QVariant();
        if (_mLanguages.empty())
            return QVariant();

        int idx = qMin(index.row(), _mLanguages.size());
        const Language& l = _mLanguages[idx];
        if (role == Qt::DecorationRole)
        {
          return QIcon(":/flags/"+l.countryName()+".png");
        }

        if (role == Qt::DisplayRole)
        {
            switch (index.column())
            {
            case 0:
                return l.name();
            case 1:
                return l.language();
            default:
                return QVariant();
            }
        }
        return QVariant();
    }
  private:
    const LanguageList& _mLanguages;
};

QxtLanguageComboBoxPrivate::QxtLanguageComboBoxPrivate()
: _mModel(0)
{
}

void QxtLanguageComboBoxPrivate::init()
{
  // multiple connects here - we need a init() method
  connect(&qxt_p(),SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxCurrentIndexChanged(int)));
}

void QxtLanguageComboBoxPrivate::setDisplayMode(QxtLanguageComboBox::DisplayMode mode)
{
  if (_mDisplayMode == mode && _mModel != 0)
    return;

  // TODO: delete _mModel ???
  QLocale::Language currentLang = currentLanguage();
  _mDisplayMode = mode;
  if (_mDisplayMode == QxtLanguageComboBox::AllLanguages)
    _mModel = new LanguageModel(Language::getAllLanguages(), &qxt_p());
  else
    _mModel = new LanguageModel(Language::getTrLanguages(), &qxt_p());

  qxt_p().setModel(_mModel);
  qxt_p().setModelColumn(0);

  setCurrentLanguage(currentLang);
}

void QxtLanguageComboBoxPrivate::comboBoxCurrentIndexChanged(int)
{
  handleLanguageChange();
}

void QxtLanguageComboBoxPrivate::handleLanguageChange()
{
  emit qxt_p().currentLanguageChanged(currentLanguage());
  emit qxt_p().currentLanguageNameChanged(currentLanguageName());
}

QLocale::Language QxtLanguageComboBoxPrivate::currentLanguage() const
{
  if (_mModel == NULL)
    return QLocale::C;

  QModelIndex idx = _mModel->index(qxt_p().currentIndex(), 1);
  QLocale::Language currentLang = static_cast<QLocale::Language>(idx.data().toInt());
  return currentLang;
}

QString QxtLanguageComboBoxPrivate::currentLanguageName() const
{
  return qxt_p().currentText();
}

void QxtLanguageComboBoxPrivate::setCurrentLanguage(QLocale::Language language)
{
  // column 1 is QLocale::Language
  QModelIndex start = _mModel->index(0, 1);
  QModelIndexList result = _mModel->match(start, Qt::DisplayRole, language, 1, Qt::MatchExactly);
  if (!result.isEmpty())
    qxt_p().setCurrentIndex(result.first().row());
  else
    qDebug() << "Cannot setCurrentLanguage: " << language << _mModel;

  handleLanguageChange();
}

/*!
    \class QxtLanguageComboBox QxtLanguageComboBox
    \ingroup QxtGui
    \brief An extended QComboBox to display langauges.

    QxtLanguageComboBox is a specialized combo box to display spoken languages.
    The languages are taken from QLocale::Language.

    \image html qxtlanguagecombobox.png "QxtLanguageComboBox in Plastique style."
 */

/*!
    \enum QxtLanguageComboBox::DisplayMode

    This enum describes the displayed languages.

    \sa QxtLanguageComboBox::displayMode
 */

/*!
    \fn QxtLanguageComboBox::currentLanguageChanged(const QLocale::Language& language)

    This signal is emitted whenever the current selected language has been changed.
 */

/*!
    \fn QxtLanguageComboBox::currentLanguageNameChanged(const QString& name)

    This signal is emitted whenever the current selected language has been changed.
 */


/*!
    Constructs a new QxtCountryComboBox with \a parent.
 */
QxtLanguageComboBox::QxtLanguageComboBox(QWidget* parent)
: QComboBox(parent)
{
  QXT_INIT_PRIVATE(QxtLanguageComboBox);
  setDisplayMode(AllLanguages);
  setCurrentLanguage(QLocale::system().language());
  qxt_d().init();
}

/*!
    Destructs the combo box.
 */
QxtLanguageComboBox::~QxtLanguageComboBox()
{
}

/*!
    \property QxtLanguageComboBox::currentLanguage
    \brief This property holds the current selected language.
 */
QLocale::Language QxtLanguageComboBox::currentLanguage() const
{
  return qxt_d().currentLanguage();
}

/*!
    \property QxtLanguageComboBox::currentLanguageName
    \brief This property holds the name of the current selected language.
 */
QString QxtLanguageComboBox::currentLanguageName() const
{
  return qxt_d().currentLanguageName();
}

void QxtLanguageComboBox::setCurrentLanguage(QLocale::Language language)
{
  qxt_d().setCurrentLanguage(language);
}

/*!
    \property QxtLanguageComboBox::displayMode
    \brief This property holds the display mode of the widget.
 */
void QxtLanguageComboBox::setDisplayMode(DisplayMode mode)
{
  qxt_d().setDisplayMode(mode);
}

QxtLanguageComboBox::DisplayMode QxtLanguageComboBox::displayMode() const
{
  return qxt_d().displayMode();
}
