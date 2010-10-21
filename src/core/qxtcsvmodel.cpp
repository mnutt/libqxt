/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtCore module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

/*!
\class QxtCsvModel
\inmodule QxtCore
\brief The QxtCsvModel class provides a QAbstractTableModel for CSV Files
 */

/*!
\fn QxtCsvModel::QxtCsvModel(QObject *parent = 0);
Constructs a new QxtCsvModel with \a parent
*/

/*!
\fn QxtCsvModel::~QxtCsvModel();
Destructor
*/

/*!
\fn QxtCsvModel::QxtCsvModel(QIODevice *file, QObject *parent=0, bool withHeader = false, QChar separator= ',')
constructs a QxtCsvModel from a QIODevice \a file as source
\a withHeader specifies if the data on the device contains a header or not.
\a separator is the separator to use for the columns. most widely used separators are ','  '\\t' ';'
*/

/*!
\fn QxtCsvModel::QxtCsvModel(const QString filename, QObject *parent = 0, bool withHeader = false, QChar separator = ',')
constructs a QxtCsvModel from \a filename as source
\a withHeader specifies if the data in the file contains a header or not.
\a separator is the separator to use for the columns. most widely used separators are ','  '\\t' ';'
*/

/*!
\fn  void QxtCsvModel::setSource(QIODevice *file, bool withHeader = false, QChar separator = ',');
reads the cvs data from \a file
\a withHeader specifies if the data on the device contains a header or not.
\a separator is the separator to use for the columns. most widely used separators are ','  '\\t' ';'
*/


/*!
\fn    void QxtCsvModel::setSource(const QString filename, bool withHeader = false, QChar separator = ',');
reads the cvs data from \a filename
\a withHeader specifies if the data in the file contains a header or not.
\a separator is the separator to use for the columns. most widely used separators are ','  '\\t' ';'
*/



/*!
\fn   void QxtCsvModel::toCSV(QIODevice *file, bool withHeader = false, QChar separator = ',');
writes the cvs data to \a file
\a withHeader specifies if to write the header or not
\a separator is the separator to use for the columns. most widely used separators are ','  '\\t' ';'
*/


/*!
\fn    void QxtCsvModel::toCSV(const QString filename, bool withHeader = false, QChar separator = ',');
writes the cvs data to \a filename
\a withHeader specifies if to write the header or not
\a separator is the separator to use for the columns. most widely used separators are ','  '\\t' ';'
*/



#include "qxtcsvmodel.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

class QxtCsvModelPrivate : public QxtPrivate<QxtCsvModel>
{
public:
    QxtCsvModelPrivate() : csvData(), header(), maxColumn(0), quoteMode(QxtCsvModel::DefaultQuoteMode)
    {}
    QXT_DECLARE_PUBLIC(QxtCsvModel)

    QList<QStringList> csvData;
    QStringList header;
    int maxColumn;
    QxtCsvModel::QuoteMode quoteMode;
};

QxtCsvModel::QxtCsvModel(QObject *parent) : QAbstractTableModel(parent)
{
    QXT_INIT_PRIVATE(QxtCsvModel);
}

QxtCsvModel::QxtCsvModel(QIODevice *file, QObject *parent, bool withHeader, QChar separator) : QAbstractTableModel(parent)
{
    QXT_INIT_PRIVATE(QxtCsvModel);
    setSource(file, withHeader, separator);
}

QxtCsvModel::QxtCsvModel(const QString filename, QObject *parent, bool withHeader, QChar separator) : QAbstractTableModel(parent)
{
    QXT_INIT_PRIVATE(QxtCsvModel);
    QFile src(filename);
    setSource(&src, withHeader, separator);
}

QxtCsvModel::~QxtCsvModel()
{}

/*!
    \reimp
 */
int QxtCsvModel::rowCount(const QModelIndex& parent) const
{
    if (parent.row() != -1 && parent.column() != -1) return 0;
    return qxt_d().csvData.count();
}

/*!
    \reimp
 */
int QxtCsvModel::columnCount(const QModelIndex& parent) const
{
    if (parent.row() != -1 && parent.column() != -1) return 0;
    return qxt_d().maxColumn;
}

/*!
    \reimp
 */
QVariant QxtCsvModel::data(const QModelIndex& index, int role) const
{
    if(index.parent() != QModelIndex()) return QVariant();
    if(role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::UserRole) {
        if(index.row() < 0 || index.column() < 0 || index.row() >= rowCount())
            return QVariant();
        const QStringList& row = qxt_d().csvData[index.row()];
        if(index.column() >= row.length())
            return QVariant();
        return row[index.column()];
    }
    return QVariant();
}

/*!
    \reimp
 */
QVariant QxtCsvModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section < qxt_d().header.count() && orientation == Qt::Horizontal && (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::UserRole))
        return qxt_d().header[section];
    else
        return QAbstractTableModel::headerData(section, orientation, role);
}

void QxtCsvModel::setSource(const QString filename, bool withHeader, QChar separator, QTextCodec* codec)
{
    QFile src(filename);
    setSource(&src, withHeader, separator, codec);
}

void QxtCsvModel::setSource(QIODevice *file, bool withHeader, QChar separator, QTextCodec* codec)
{
    QxtCsvModelPrivate* d_ptr = &qxt_d();
    bool headerSet = !withHeader;
    if(!file->isOpen())
        file->open(QIODevice::ReadOnly);
    if(withHeader)
        d_ptr->maxColumn = 0;
    else
        d_ptr->maxColumn = d_ptr->header.size();
    d_ptr->csvData.clear();
    QStringList row;
    QString field;
    QChar quote;
    QChar ch, buffer(0);
    bool readCR = false;
    QTextStream stream(file);
    if(codec) {
        stream.setCodec(codec);
    } else {
        stream.setAutoDetectUnicode(true);
    }
    while(!stream.atEnd()) {
        if(buffer != QChar(0)) {
            ch = buffer; 
            buffer = QChar(0);
        } else {
            stream >> ch;
        }
        if(ch == '\n' && readCR) 
            continue;
        else if(ch == '\r')
            readCR = true;
        else
            readCR = false;
        if(ch.category() == QChar::Separator_Line || ch.category() == QChar::Separator_Paragraph || ch.category() == QChar::Other_Control) {
            row << field;
            field.clear();
            if(!row.isEmpty()) {
                if(!headerSet) {
                    d_ptr->header = row;
                    headerSet = true;
                } else {
                    d_ptr->csvData.append(row);
                }
                if(row.length() > d_ptr->maxColumn) {
                    d_ptr->maxColumn = row.length();
                }
            }
            row.clear();
        } else if((d_ptr->quoteMode & DoubleQuote && ch == '"') || (d_ptr->quoteMode & SingleQuote && ch == '\'')) {
            quote = ch;
            do {
                stream >> ch;
                if(ch == '\\' && d_ptr->quoteMode & BackslashEscape) {
                    stream >> ch;
                } else if(ch == quote) {
                    if(d_ptr->quoteMode & TwoQuoteEscape) {
                        stream >> buffer;
                        if(buffer == quote) {
                            buffer = QChar(0);
                            field.append(ch);
                            continue;
                        }
                    }
                    break;
                }
                field.append(ch);
            } while(!stream.atEnd());
        } else if(ch == separator) {
            row << field;
            field.clear();
        } else {
            field.append(ch);
        }
    }
    if(!field.isEmpty()) 
        row << field;
    if(!row.isEmpty()) {
        if(!headerSet)
            d_ptr->header = row;
        else
            d_ptr->csvData.append(row);
    }
    file->close();
}

/*!
    \reimp
 */
void QxtCsvModel::setHeaderData(const QStringList data)
{
    qxt_d().header = data;
    emit headerDataChanged(Qt::Horizontal, 0, data.count());
}

/*!
    \reimp
 */
bool QxtCsvModel::setData(const QModelIndex& index, const QVariant& data, int role)
{
    if (index.parent() != QModelIndex()) return false;

    if(role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::UserRole) {
        if(index.row() >= rowCount() || index.column() >= columnCount() || index.row() < 0 || index.column() < 0) return false;
        QStringList& row = qxt_d().csvData[index.row()];
        while(row.length() <= index.column())
            row << QString();
        row[index.column()] = data.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/*!
    \reimp
 */
bool QxtCsvModel::insertRow(int row, const QModelIndex& parent)
{
    return insertRows(row, 1, parent);
}

/*!
    \reimp
 */
bool QxtCsvModel::insertRows(int row, int count, const QModelIndex& parent)
{
    if (parent != QModelIndex() || row < 0) return false;
    emit beginInsertRows(parent, row, row + count);
    QxtCsvModelPrivate& d_ptr = qxt_d();
    if(row >= rowCount()) {
        for(int i = 0; i < count; i++) d_ptr.csvData << QStringList();
    } else {
        for(int i = 0; i < count; i++) d_ptr.csvData.insert(row, QStringList());
    }
    emit endInsertRows();
    return true;
}

/*!
    \reimp
 */
bool QxtCsvModel::removeRow(int row, const QModelIndex& parent)
{
    return removeRows(row, 1, parent);
}

/*!
    \reimp
 */
bool QxtCsvModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (parent != QModelIndex() || row < 0) return false;
    if (row >= rowCount()) return false;
    if (row + count >= rowCount()) count = rowCount() - row;
    emit beginRemoveRows(parent, row, row + count);
    QxtCsvModelPrivate& d_ptr = qxt_d();
    for (int i = 0;i < count;i++)
        d_ptr.csvData.removeAt(row);
    emit endRemoveRows();
    return true;
}

/*!
    \reimp
 */
bool QxtCsvModel::insertColumn(int col, const QModelIndex& parent)
{
    return insertColumns(col, 1, parent);
}

/*!
    \reimp
 */
bool QxtCsvModel::insertColumns(int col, int count, const QModelIndex& parent)
{
    if (parent != QModelIndex() || col < 0) return false;
    emit beginInsertColumns(parent, col, col + count);
    QxtCsvModelPrivate& d_ptr = qxt_d();
    for(int i = 0; i < rowCount(); i++) {
        QStringList& row = d_ptr.csvData[i];
        while(col >= row.length()) row.append(QString());
        for(int j = 0; j < count; j++) {
            row.insert(col, QString());
        }
    }
    for(int i = 0; i < count ;i++)
        d_ptr.header.insert(col, QString());
    d_ptr.maxColumn += count;
    emit endInsertColumns();
    return true;
}

/*!
    \reimp
 */
bool QxtCsvModel::removeColumn(int col, const QModelIndex& parent)
{
    return removeColumns(col, 1, parent);
}

/*!
    \reimp
 */
bool QxtCsvModel::removeColumns(int col, int count, const QModelIndex& parent)
{
    if (parent != QModelIndex() || col < 0) return false;
    if (col >= columnCount()) return false;
    if (col + count >= columnCount()) count = columnCount() - col;
    emit beginRemoveColumns(parent, col, col + count);
    QxtCsvModelPrivate& d_ptr = qxt_d();
    QString before, after;
    for(int i = 0; i < rowCount(); i++) {
        for(int j = 0; j < count; j++) {
            d_ptr.csvData[i].removeAt(col);
        }
    }
    for(int i = 0; i < count; i++)
        d_ptr.header.removeAt(col);
    emit endRemoveColumns();
    return true;
}

static QString qxt_addCsvQuotes(QxtCsvModel::QuoteMode mode, QString field)
{
    bool addDoubleQuotes = ((mode & QxtCsvModel::DoubleQuote) && field.contains('"'));
    bool addSingleQuotes = ((mode & QxtCsvModel::SingleQuote) && field.contains('\''));
    bool quoteField = (mode & QxtCsvModel::AlwaysQuoteOutput) || addDoubleQuotes || addSingleQuotes;
    if(quoteField && !addDoubleQuotes && !addSingleQuotes) {
        if(mode & QxtCsvModel::DoubleQuote)
            addDoubleQuotes = true;
        else if(mode & QxtCsvModel::SingleQuote)
            addSingleQuotes = true;
    } 
    if(mode & QxtCsvModel::BackslashEscape) {
        if(addDoubleQuotes) 
            return '"' + field.replace("\\", "\\\\").replace("\"", "\\\"") + '"';
        if(addSingleQuotes)
            return '\'' + field.replace("\\", "\\\\").replace("'", "\\'") + '\'';
    } else {
        if(addDoubleQuotes) 
            return '"' + field.replace("\"", "\"\"") + '"';
        if(addSingleQuotes)
            return '\'' + field.replace("'", "''") + '\'';
    }
    return field;
}

void QxtCsvModel::toCSV(QIODevice* dest, bool withHeader, QChar separator, QTextCodec* codec)
{
    QxtCsvModelPrivate& d_ptr = qxt_d();
    int row, col, rows, cols;
    rows = rowCount();
    cols = columnCount();
    QString data;
    if(!dest->isOpen()) dest->open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream stream(dest);
    if(codec) stream.setCodec(codec);
    if(withHeader) {
        data = "";
        for(col = 0; col < cols; ++col) {
            if(col > 0) data += separator;
            data += qxt_addCsvQuotes(d_ptr.quoteMode, d_ptr.header.at(col)); 
        }
        stream << data << endl;
    }
    for(row = 0; row < rows; ++row)
    {
        const QStringList& rowData = d_ptr.csvData[row];
        data = "";
        for(col = 0; col < cols; ++col) {
            if(col > 0) data += separator;
            if(col < rowData.length())
                data += qxt_addCsvQuotes(d_ptr.quoteMode, rowData.at(col)); 
            else
                data += qxt_addCsvQuotes(d_ptr.quoteMode, QString());; 
        }
        stream << data << endl;
    }
    stream << flush;
    dest->close();
}

void QxtCsvModel::toCSV(const QString filename, bool withHeader, QChar separator, QTextCodec* codec)
{
    QFile dest(filename);
    toCSV(&dest, withHeader, separator, codec);
}

/*!
    \reimp
 */
Qt::ItemFlags QxtCsvModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

/**
 * Returns the current quoting mode.
 * \sa setQuoteMode
 */
QxtCsvModel::QuoteMode QxtCsvModel::quoteMode() const
{
    return qxt_d().quoteMode;
}

/**
 * Sets the current quoting mode. The default quoting mode is BothQuotes | BackslashEscape.
 *
 * The quoting mode determines what kinds of quoting is used for reading and writing CSV files.
 * \sa quoteMode
 * \sa QuoteOption
 */
void QxtCsvModel::setQuoteMode(QuoteMode mode)
{
    qxt_d().quoteMode = mode;
}
