/***************************************************************************
 *   QxtCsvModel.h: a table model onto a CSV file                          *
 *   Copyright (C) 2005-2007 by Adam Higerd                                *
 *   ahigerd@stratitec.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef QXTCSVMODEL_H
#define QXTCSVMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QIODevice>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QModelIndex>
#include <QxtPimpl.h>

/**
@author Adam Higerd
*/
class QxtCsvModelPrivate;
class QxtCsvModel : public QAbstractTableModel
{
Q_OBJECT
public:
    QxtCsvModel(QObject *parent = 0);
    QxtCsvModel(QIODevice *file, QObject *parent = 0, bool withHeader = false, QChar separator = ',');
    QxtCsvModel(const QString filename, QObject *parent = 0, bool withHeader = false, QChar separator = ',');
    ~QxtCsvModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& data, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void setHeaderData(const QStringList data);

    bool insertRow(int row, const QModelIndex& parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
    bool removeRow(int row, const QModelIndex& parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
    bool insertColumn(int col, const QModelIndex& parent = QModelIndex());
    bool insertColumns(int col, int count, const QModelIndex& parent = QModelIndex());
    bool removeColumn(int col, const QModelIndex& parent = QModelIndex());
    bool removeColumns(int col, int count, const QModelIndex& parent = QModelIndex());

    void setSource(QIODevice *file, bool withHeader = false, QChar separator = ',');
    void setSource(const QString filename, bool withHeader = false, QChar separator = ',');

    void toCSV(QIODevice *file, bool withHeader = false, QChar separator = ',');
    void toCSV(const QString filename, bool withHeader = false, QChar separator = ',');

    Qt::ItemFlags flags(const QModelIndex& index) const;

private:
    QXT_DECLARE_PRIVATE(QxtCsvModel);
};

#endif
