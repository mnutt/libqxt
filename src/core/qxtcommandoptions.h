/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/

#ifndef QXTCOMMANDOPTIONS_DEFINED
#define QXTCOMMANDOPTIONS_DEFINED
#include <qxtglobal.h>
#include <qxtpimpl.h>
#include <QStringList>
#include <QVariant>
#include <QCoreApplication>     // for Q_DECLARE_TR_FUNCTIONS
#include <QMultiHash>
#include <QFlags>
class QxtCommandOptionsPrivate;
class QTextStream;
class QIODevice;

struct QXT_CORE_EXPORT QxtCommandOptions
{
Q_DECLARE_TR_FUNCTIONS(QxtCommandOptions)

public:
    enum FlagStyle { DoubleDash, SingleDash, Slash };
    enum ParamStyle { Space = 1, Equals = 2, SpaceAndEquals = 3 };
    enum ParamType { NoValue = 0, Optional = 1, Required = 2, AllowMultiple = 4, Undocumented = 8 };
    Q_DECLARE_FLAGS(ParamTypes, ParamType)

    QxtCommandOptions();

    void setFlagStyle(FlagStyle style);
    FlagStyle flagStyle() const;
    void setParamStyle(ParamStyle style);
    ParamStyle paramStyle() const;
    void setScreenWidth(quint16 width);
    quint16 screenWidth() const;

    void addSection(const QString& name);
    void add(const QString& name, const QString& desc = QString(), ParamTypes paramType = NoValue, int group = -1);
    void alias(const QString& from, const QString& to);

    QStringList positional() const;
    QStringList unrecognized() const;
    int count(const QString& name) const;
    QVariant value(const QString& name) const;
    QMultiHash<QString, QVariant> parameters() const;

    void parse(QStringList params);
    
    void showUsage(bool showQtOptions = false, QIODevice* device = 0) const;
    void showUsage(bool showQtOptions, QTextStream& stream) const;
    QString getUsage(bool showQtOptions = false) const;
    
    bool showUnrecognizedWarning(QIODevice* device = 0) const;
    bool showUnrecognizedWarning(QTextStream& stream) const;
    QString getUnrecognizedWarning() const;

private:
    QXT_DECLARE_PRIVATE(QxtCommandOptions);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QxtCommandOptions::ParamTypes)

#endif
