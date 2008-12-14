/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
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
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QXTVIRALCSV_H
#define QXTVIRALCSV_H

#include <QAbstractItemModel>
#include "qxtglobal.h"
#include "qxtpimpl.h"


template <class Q,class Y>
class QxtViralAdapter;

namespace  Viral
{class Csv;}

class QxtViralCsvPrivate;
class QXT_VIRAL_EXPORT QxtViralCsv : public QAbstractItemModel
{
    Q_OBJECT
public:
    QxtViralCsv(QString filename,QChar seperator=';',bool witheaders=true ,QObject *parent = 0 );
    virtual ~QxtViralCsv();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;


    friend class QxtViralAdapter<QxtViralCsv,Viral::Csv>;
private:
    QXT_DECLARE_PRIVATE(QxtViralCsv);
};

#endif
