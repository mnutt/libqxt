#include <QCoreApplication>
#include <QLocale>
#include <QTextStream>
#include <QDateTime>
#include <QMetaEnum>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>

QString capitalize(const QString& str);

static const char* qxt_header =
"/****************************************************************************\n"
" **\n"
" ** Copyright (C) Qxt Foundation. Some rights reserved.\n"
" **\n"
" ** This file is part of the QxtCore module of the Qxt library.\n"
" **\n"
" ** This library is free software; you can redistribute it and/or modify it\n"
" ** under the terms of the Common Public License, version 1.0, as published\n"
" ** by IBM, and/or under the terms of the GNU Lesser General Public License,\n"
" ** version 2.1, as published by the Free Software Foundation.\n"
" **\n"
" ** This file is provided \"AS IS\", without WARRANTIES OR CONDITIONS OF ANY\n"
" ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY\n"
" ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR\n"
" ** FITNESS FOR A PARTICULAR PURPOSE.\n"
" **\n"
" ** You should have received a copy of the CPL and the LGPL along with this\n"
" ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files\n"
" ** included with the source distribution for more information.\n"
" ** If you did not receive a copy of the licenses, contact the Qxt Foundation.\n"
" **\n"
" ** <http://libqxt.org>  <foundation@libqxt.org>\n"
" **\n"
" ****************************************************************************/\n";

struct CCYInfo
{
  CCYInfo()
  {}
  CCYInfo(const QString& country, const QString& ccyname, const QString& code)
  : _mCountry(country), _mCurrencyName(ccyname), _mCurrencyCode(code)
  {}

  QString getEnum()
  {
    QString str = capitalize(_mCurrencyName).remove(' ');
    str.remove(QRegExp("\\(.*\\)")).remove('\'').remove('-').trimmed().simplified();
    return str;
  }

  QString _mCountry;
  QString _mCurrencyName;
  QString _mCurrencyCode;
};

typedef QList<CCYInfo> CCYInfoList;

struct CountryInfo
{
  CountryInfo()
  {}
  CountryInfo(const QString& country, const QString& code2, const QString& code3,
              const QString& continent)
  : _mCountry(country), _mCode2(code2), _mCode3(code3), _mContinent(continent)
  {}

  QString _mCountry;
  QString _mCode2;
  QString _mCode3;
  QString _mContinent;
};

typedef QList<CountryInfo> CountryInfoList;

CCYInfoList load()
{
  CCYInfoList ret;
  ret.push_back(CCYInfo("DEFAULT", "No Currency", "   "));
  ret.push_back(CCYInfo("ANTARCTICA", "No Currency", "   "));
  QFile data("currency.txt");
  if (data.open(QFile::ReadOnly))
  {
    QTextStream fin(&data);
    QString line;
    while(true)
    {
       line = fin.readLine();
       if (line.isNull())
         break;

       if (line.contains("ANTARCTICA"))
         continue;

       QStringList cells = line.split('\t');
//       qDebug() << cells;
       ret.push_back(CCYInfo(cells[0].remove('"').trimmed(), cells[1].remove('"').trimmed(), cells[2].remove('"').trimmed()));
    }
  }

  return ret;
}

CountryInfoList loadCountries()
{
  CountryInfoList ret;
/*  ret.push_back(CCYInfo("DEFAULT", "No Currency", "   "));
  ret.push_back(CCYInfo("ANTARCTICA", "No Currency", "   "));*/
  QFile data("country.txt");
  if (data.open(QFile::ReadOnly))
  {
    QTextStream fin(&data);
    QString line;
    while(true)
    {
       line = fin.readLine();
       if (line.isNull())
         break;

//        if (line.contains("ANTARCTICA"))
//          continue;

       QStringList cells = line.split('\t');
//       qDebug() << cells;
       QString c0 = cells[0].remove('"').trimmed();
       QString c1 = cells[1].remove('"').trimmed();
       QString c2 = cells[2].remove('"').trimmed();
       QString c3 = cells[3].remove('"').trimmed();
       ret.push_back(CountryInfo(c0, c1, c2, c3));
    }
  }

  return ret;
}

typedef QMap<QString, QString> CurrencySymbolMap;

CurrencySymbolMap loadSymbols()
{
  CurrencySymbolMap ret;
/*  ret.push_back(CCYInfo("DEFAULT", "No Currency", "   "));
  ret.push_back(CCYInfo("ANTARCTICA", "No Currency", "   "));*/
  QFile data("currency_symbols.txt");
  if (data.open(QFile::ReadOnly))
  {
    QTextStream fin(&data);
    QString line;
    while(true)
    {
       line = fin.readLine();
       if (line.isNull())
         break;

       QStringList cells = line.split('\t');
       QStringList hexs = cells[1].trimmed().split(',');
       for (int i = 0; i < hexs.size(); i++)
         hexs[i] = "0x" + hexs[i].trimmed();

       ret[cells[0].trimmed()] = QString::number(hexs.size())+ "," + hexs.join(",");
//       qDebug() << cells;
//       ret.push_back(CCYInfo(cells[0].replace("\"", "").trimmed(), cells[1].replace("\"", "").trimmed(), cells[2].replace("\"", "").trimmed()));
    }
  }

  return ret;
}

QString capitalize(const QString& str)
{
  QStringList words = str.split(' ');
  for(int  i = 0; i < words.size(); ++i)
  {
     words[i][0] = words[i][0].toUpper();
  }

  return words.join(" ");
}

CCYInfo match(const QString& country, const CCYInfoList& ccys)
{
  for(int i = 0; i < ccys.size(); i++)
  {
    QString countrystr = ccys[i]._mCountry.trimmed();
//    qDebug() << countrystr;
    countrystr = capitalize(countrystr.toLower()).remove(QRegExp("\\(.*\\)")).remove(' ').remove('"');
    if (countrystr == country)
      return ccys[i];
    if (countrystr.startsWith(country, Qt::CaseInsensitive))
      return ccys[i];
    if (country.startsWith(countrystr, Qt::CaseInsensitive))
      return ccys[i];
    if (countrystr.endsWith(country, Qt::CaseInsensitive))
      return ccys[i];
    if (country.endsWith(countrystr, Qt::CaseInsensitive))
      return ccys[i];
  }

  qDebug() << country << " not found!";
  return CCYInfo();
}

void printCurrencyEnum(QTextStream& out, const QList<QString>& keys )
{
  out << "  enum Currency{" << endl;
  out << "    NoCurrency = 0," << endl;

  int enumCount = 1;
  for (int i = 0; i < keys.size(); i++)
  {
    if (keys[i] == "NoCurrency")
      continue;

    out << "    " << keys[i] << " = " << enumCount++<< "," << endl;
  }

  out << "    LastCurrency = " << keys[keys.size()-1] << endl;
  out << "};" << endl;
}

void printCurrencyNames(QTextStream& out, const QMap<QString, CCYInfo>& printed)
{
  QList<QString> keys  = printed.keys();
  out << "static const char* currency_names[] = {" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"*No Currency*\"), // NoCurrency" << endl;
  for (int i = 0; i < keys.size(); i++)
  {
    if (keys[i] == "NoCurrency")
      continue;

    QString currencyName = printed[keys[i]]._mCurrencyName;
    out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \""
        << currencyName.remove(QRegExp("\\(.*\\)")).trimmed()
        << "\"), // " << keys[i] << endl;
  }
  out << "};" << endl;
}

void printCurrencyCode(QTextStream& out, const QMap<QString, CCYInfo>& printed)
{
  QList<QString> keys  = printed.keys();
  out << "static const unsigned char currency_code_list[] = " << endl;
  out << "\"   \" // NoCurrency" << endl;
  for (int i = 0; i < keys.size(); i++)
  {
    if (keys[i] == "NoCurrency")
      continue;

    out << "\"" << printed[keys[i]]._mCurrencyCode.trimmed() << "\" // " << keys[i] << endl;
  }
  out << ";" << endl;
}

void printCurrencyForCountryList(QTextStream& out, const CCYInfoList& ccys)
{
  int failures = 0;
  out << "static QxtLocale::Currency currency_for_country_list[] = {" << endl;
  for (int c = 0; c < QLocale::LastCountry; ++c)
  {
    QString country = QLocale::countryToString((QLocale::Country)c);
    CCYInfo ccy = match(country, ccys);
    if (ccy._mCountry.isNull())
      failures++;

    if (!ccy._mCountry.isNull())
      out << " QxtLocale::" << qPrintable(ccy.getEnum()) << ", // " << country << endl;
    else
      out << " QxtLocale::NoCurrency, // " << country << endl;

  }
  out << "};" << endl;

  qDebug() << failures << " missing matches!";
}

void printCurrencySymbols(QTextStream& out, const QMap<QString, CCYInfo>& printed,
     const CurrencySymbolMap& symbolmap)
{
  QList<QString> keys  = printed.keys();
  out << "static QChar symbol_for_country_list[][5] =" << endl;
  out << "{" << endl;
  out << "{  }, // NoCurrency" << endl;
  for (int i = 0; i < keys.size(); i++)
  {
    if (keys[i] == "NoCurrency")
      continue;

    QString hexcode = symbolmap[printed[keys[i]]._mCurrencyCode];
    out << "{ " << hexcode << " }, // " << keys[i] << endl;
  }
  out << "}" << endl;
  out << ";" << endl;
}

void printCountryCode(QTextStream& out, const QMap<QString, CountryInfo>& countriesMap, bool printTwo)
{
  if (printTwo)
    out << "static const unsigned char two_letter_country_code_list[] =" << endl;
  else
    out << "static const unsigned char three_letter_country_code_list[] =" << endl;

  for(int i = 0; i <= QLocale::LastCountry; i++)
  {
    QString countryToString = QLocale::countryToString((QLocale::Country)i);
    if (i == QLocale::AnyCountry)
    {
      if (printTwo)
        out << "\"" << "  " << "\" // " << countryToString << endl;
      else
        out << "\"" << "   " << "\" // " << countryToString << endl;

      continue;
    }

    CountryInfo country = countriesMap[countryToString];
    if(!country._mCountry.isNull())
    {
      if (printTwo)
        out << "\"" << country._mCode2 << "\" // " << country._mCountry << endl;
      else
        out << "\"" << country._mCode3 << "\" // " << country._mCountry << endl;
    }
    else
    {
      if (printTwo)
        out << "\"" << "--" << "\" // " << countryToString << endl;
      else
        out << "\"" << "---" << "\" // " << countryToString << endl;
    }
  }
  out << ";" << endl;
}

void printContinentNames(QTextStream& out)
{
  out << "static const char* continent_names[] = {" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"None\"), // None" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"NorthAmerica\"), // NorthAmerica" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"SouthAmerica\"), // SouthAmerica" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"Europe\"), // Europe" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"Africa\"), // Africa" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"Asia\"), // Asia" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"Australia\"), // Australia" << endl;
  out << "  QT_TRANSLATE_NOOP(\"QxtLocale\", \"Antarctica\"), // Antarctica" << endl;
  out << "};" << endl;
}

void printContinentForCountryList(QTextStream& out, const QMap<QString, CountryInfo>& countriesMap)
{
/*
 continent_for_country_list[] = {
};
*/
  out << "static const QxtLocale::Continent continent_for_country_list[] = {" << endl;

  for(int i = 0; i <= QLocale::LastCountry; i++)
  {
    QString countryToString = QLocale::countryToString((QLocale::Country)i);
    if (i == QLocale::AnyCountry)
    {
      out << "QxtLocale::None, // " << countryToString << endl;
      continue;
    }

    CountryInfo country = countriesMap[countryToString];
    if(!country._mCountry.isNull())
    {
      out << "QxtLocale::" << country._mContinent << ", // " << country._mCountry << endl;
    }
    else
    {
      out << "" << "Unknown" << ", // " << countryToString << endl;
    }
  }
  out << "};" << endl;
}

void printQLocateEnumsForTranslation(QTextStream& out)
{
  out << "#if 0" << endl;

  // generate languages
  {
  out << "static const char* language_strings = {" << endl;

  const QMetaObject& mo = QLocale::staticMetaObject;
  int index = mo.indexOfEnumerator("Language");
  QMetaEnum metaEnum = mo.enumerator(index);
  for (int idx = 0; idx < metaEnum.keyCount(); ++idx)
  {
    QLocale::Language l = static_cast<QLocale::Language>(metaEnum.value(idx));
    if (l == QLocale::LastLanguage)
      continue;

    out << "  QT_TRANSLATE_NOOP(\"QLocale\", \"" << metaEnum.key(idx) << "\")," << endl;
  }
  out << "};" << endl;
  }

  // generate countries
  {
  out << "static const char* countries_strings = {" << endl;

  const QMetaObject& mo = QLocale::staticMetaObject;
  int index = mo.indexOfEnumerator("Country");
  QMetaEnum metaEnum = mo.enumerator(index);
  for (int idx = 0; idx < metaEnum.keyCount(); ++idx)
  {
    QLocale::Country l = static_cast<QLocale::Country>(metaEnum.value(idx));
    if (l == QLocale::LastCountry)
      continue;

    out << "  QT_TRANSLATE_NOOP(\"QLocale\", \"" << metaEnum.key(idx) << "\")," << endl;
  }
  out << "};" << endl;
  out << "#endif" << endl;
  out << endl;
  }
}

void printHelp(QTextStream& out)
{
  out << endl;
  out << "This tool is used to generate code used by QxtLocale." << endl;
  out << "The generated code is written to stdout." << endl;
  out << endl;
  out << "Following options are known:" << endl;
  out << " help                   - displays this help." << endl;
  out << " currency-enum          - generates enum QxtLocale::Currency." << endl;
  out << " qlocate-translations   - generates dummy C++ code for translations of" << endl;
  out << "                          enums QLocale::Language and QLocale::Country." << endl;
  out << " <no argument>          - generated qxt_locale_data_p.h" << endl;
  out << endl;
}

int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);

  QTextStream out(stdout);

  if (app.arguments().contains("help"))
  {
    printHelp(out);
    return 0;
  }

  CCYInfoList ccys = load();
  CurrencySymbolMap symbolmap = loadSymbols();
  CountryInfoList countries = loadCountries();

  QMap<QString, CCYInfo> printed;
  for (int i = 0; i < ccys.size(); i++)
  {
    QString str = ccys[i].getEnum();
    if (printed.contains(str))
      continue;
    printed[str] = ccys[i];
  }

  QMap<QString, CountryInfo> countriesMap;
  for (int i = 0; i < countries.size(); i++)
  {
    countriesMap[countries[i]._mCountry] = countries[i];
  }
  QList<QString> keys  = printed.keys();

  if (app.arguments().contains("currency-enum"))
  {
    printCurrencyEnum(out, keys);
  }
  else if (app.arguments().contains("qlocate-translations"))
  {
    out << qxt_header << endl;
    out << "//" << endl;
    out << "// Generated on " << QDateTime::currentDateTime().toString() << endl;
    out << "//  for Qt " << QT_VERSION_STR << endl;
    out << "//" << endl;
    out << endl;
    printQLocateEnumsForTranslation(out);
  }
  else
  {
    out << qxt_header << endl;
    out << "//" << endl;
    out << "// Generated on " << QDateTime::currentDateTime().toString() << endl;
    out << "//  for Qt " << QT_VERSION_STR << endl;
    out << "//" << endl;
    out << endl;
    out << "#ifndef QXTLOCALE_DATA_P_H" << endl;
    out << "#define QXTLOCALE_DATA_P_H" << endl;
    out << "#include <QObject>" << endl;
    out << "#include <QChar>" << endl;

    printCountryCode(out, countriesMap, true);
    printCountryCode(out, countriesMap, false);
    printCurrencyForCountryList(out, ccys);
    printCurrencyNames(out, printed);
    printCurrencySymbols(out, printed, symbolmap);
    printCurrencyCode(out, printed);
    printContinentNames(out);
    printContinentForCountryList(out, countriesMap);

    out << "#endif" << endl;
  }
}
