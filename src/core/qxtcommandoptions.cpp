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

#include "qxtcommandoptions.h"
#include <QTextStream>
#include <QIODevice>
#include <QtDebug>

/**
\class QxtCommandOptions QxtCommandOptions

\ingroup QxtCore

\brief An easy parser for command-line options

\sa QCoreApplication::arguments()
*/

static const char* qxt_qt_options[] = {
    "=style",       QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the application GUI style"),
    "=stylesheet",  QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the application stylesheet"),
    "=session",     QT_TRANSLATE_NOOP("QxtCommandOptions", "restores the application from an earlier session"),
    "widgetcount",  QT_TRANSLATE_NOOP("QxtCommandOptions", "displays debugging information about widgets"),
    "reverse",      QT_TRANSLATE_NOOP("QxtCommandOptions", "use right-to-left layout"),
#ifdef QT_DEBUG
    "nograb",       QT_TRANSLATE_NOOP("QxtCommandOptions", "never grab the mouse or keyboard"),
#endif
#if defined(QT_DEBUG) && defined(Q_WS_X11)
    "dograb",       QT_TRANSLATE_NOOP("QxtCommandOptions", "grab the mouse/keyboard even in a debugger"),
    "sync",         QT_TRANSLATE_NOOP("QxtCommandOptions", "run in synchronous mode for debugging"),
#endif
#ifdef Q_WS_WIN
    "direct3d",     QT_TRANSLATE_NOOP("QxtCommandOptions", "use Direct3D by default"),
#endif
#ifdef Q_WS_X11
    "=display",     QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the X11 display"),
    "=geometry",    QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the geometry of the first window"),
    "=font",        "",
    "=fn",          QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the default font"),
    "=background",  "", 
    "=bg",          QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the default background color"),
    "=foreground",  "",
    "=fg",          QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the default foreground color"),
    "=button",      "",
    "=btn",         QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the default button color"),
    "=name",        QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the application name"),
    "=title",       QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the application title"),
    "=visual",      QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the X11 visual type"),
    "=ncols",       QT_TRANSLATE_NOOP("QxtCommandOptions", "limit the number of colors on an 8-bit display"),
    "cmap",         QT_TRANSLATE_NOOP("QxtCommandOptions", "use a private color map"),
    "=im",          QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the input method server"),
    "noxim",        QT_TRANSLATE_NOOP("QxtCommandOptions", "disable the X Input Method"),
    "=inputstyle",  QT_TRANSLATE_NOOP("QxtCommandOptions", "sets the style used by the input method"),
#endif
    0,              0
};

static int isQtOption(const QString& param) {
    if(param[0] != '-') return 0;
    if(param[1] == '-') return 0;
    QString name = param.mid(1), value;
    bool hasEquals;
    
    if(name.indexOf('=') != -1) {
        value = param.section('=', 1);
        name = param.section('=', 0, 0);
        hasEquals = true;
    } else {
        value = "";
        hasEquals = false;
    }

    const char* option;
    bool optionHasValue;
    for(int i = 0; qxt_qt_options[i]; i += 2) {
        option = qxt_qt_options[i];
        if(option[0] == '=') {
            optionHasValue = true;
            option = option + 1; // pointer math!
        } else {
            optionHasValue = false;
        }

        if(name == option) {
            if(optionHasValue) return 2;
            return 1;
        }
    }
    
    return 0;
}

struct QxtCommandOption {
    QStringList names;
    QString canonicalName;
    QString desc;
    QStringList values;
    QxtCommandOptions::ParamTypes paramType;
    quint16 group;
};

class QxtCommandOptionsPrivate : public QxtPrivate<QxtCommandOptions> {
Q_DECLARE_TR_FUNCTIONS(QxtCommandOptions)
public:
    QXT_DECLARE_PUBLIC(QxtCommandOptions);

    QList<QxtCommandOption> options;
    QHash<QString, QxtCommandOption*> lookup;
    QHash<int, QList<QxtCommandOption*> > groups;
    QxtCommandOptions::FlagStyle flagStyle;
    QxtCommandOptions::ParamStyle paramStyle;
    QStringList positional;
    QStringList unrecognized;
    QStringList missingParams;
    int screenWidth;
    bool parsed;

    QxtCommandOption* findOption(const QString& name);
    const QxtCommandOption* findOption(const QString& name) const;
    void setOption(QxtCommandOption* option, const QString& value = QString());
    void parse(const QStringList& params);
};

QxtCommandOption* QxtCommandOptionsPrivate::findOption(const QString& name) {
    // The backwards loop will find what we're looking for more quickly in the
    // typical use case, where you add aliases immediately after adding the option.
    for(int i = options.count() - 1; i >= 0; --i) {
        if(options[i].canonicalName == name) return &options[i];
    }
    qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("option \"%1\" not found").arg(name));
    return 0;
}

const QxtCommandOption* QxtCommandOptionsPrivate::findOption(const QString& name) const {
    // The backwards loop will find what we're looking for more quickly in the
    // typical use case, where you add aliases immediately after adding the option.
    for(int i = options.count() - 1; i >= 0; --i) {
        if(options[i].canonicalName == name) return &(options.at(i));
    }
    qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("option \"%1\" not found").arg(name));
    return 0;
}

QxtCommandOptions::QxtCommandOptions() {
    QXT_INIT_PRIVATE(QxtCommandOptions);
    qxt_d().screenWidth = 80;
    qxt_d().parsed = false;
#ifdef Q_OS_WIN
    setFlagStyle(Slash);
    setParamStyle(Equals);
#else
    setFlagStyle(DoubleDash);
    setParamStyle(SpaceAndEquals);
#endif
}

void QxtCommandOptions::setFlagStyle(FlagStyle style) {
    qxt_d().flagStyle = style;
}

QxtCommandOptions::FlagStyle QxtCommandOptions::flagStyle() const {
    return qxt_d().flagStyle;
}

void QxtCommandOptions::setParamStyle(ParamStyle style) {
    qxt_d().paramStyle = style;
}

QxtCommandOptions::ParamStyle QxtCommandOptions::paramStyle() const {
    return qxt_d().paramStyle;
}

void QxtCommandOptions::setScreenWidth(quint16 width) {
    qxt_d().screenWidth = width;
}

quint16 QxtCommandOptions::screenWidth() const {
    return qxt_d().screenWidth;
}

void QxtCommandOptions::addSection(const QString& name) {
    QxtCommandOption option;
    option.canonicalName = QString();
    option.desc = name;
    qxt_d().options.append(option);
}

void QxtCommandOptions::add(const QString& name, const QString& desc, ParamTypes paramType, int group) {
    QxtCommandOption option;
    option.canonicalName = name;
    option.desc = desc;
    option.paramType = paramType;
    option.group = group;
    qxt_d().options.append(option);
    if(group != -1)
        qxt_d().groups[group].append(&(qxt_d().options.last()));
    alias(name, name);
}

void QxtCommandOptions::alias(const QString& from, const QString& to) {
    QxtCommandOption* option = qxt_d().findOption(from);
    if(!option) return; // findOption outputs the warning
    option->names.append(to);
    qxt_d().lookup[to] = option;
    if(option->paramType & Optional && qxt_d().flagStyle == DoubleDash && to.length() == 1)
        qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("Short options cannot have optional parameters"));
}

QStringList QxtCommandOptions::positional() const {
    if(!qxt_d().parsed)
        qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("positional() called before parse()"));
    return qxt_d().positional;
}

QStringList QxtCommandOptions::unrecognized() const {
    if(!qxt_d().parsed)
        qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("unrecognized() called before parse()"));
    return qxt_d().unrecognized + qxt_d().missingParams;
}

int QxtCommandOptions::count(const QString& name) const {
    if(!qxt_d().parsed)
        qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("count() called before parse()"));
    const QxtCommandOption* option = qxt_d().findOption(name);
    if(!option) return 0; // findOption outputs the warning
    return option->values.count();
}

QVariant QxtCommandOptions::value(const QString& name) const {
    if(!qxt_d().parsed)
        qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("value() called before parse()"));
    const QxtCommandOption* option = qxt_d().findOption(name);
    if(!option) return QVariant(); // findOption outputs the warning
    int ct = option->values.count();
    if(ct == 0) return QVariant();
    if(ct == 1) return option->values.first();
    return option->values;
}

QMultiHash<QString, QVariant> QxtCommandOptions::parameters() const {
    if(!qxt_d().parsed)
        qWarning() << qPrintable(QString("QxtCommandOptions: ")+tr("unrecognized() called before parse()"));
    QMultiHash<QString, QVariant> params;
    int ct;
    foreach(QxtCommandOption option, qxt_d().options) {
        ct = option.values.count();
        if(!ct) {
            continue;
        } else if(!(option.paramType & (Optional | Required))) {
            params.insert(option.canonicalName, true);
        } else {
            foreach(QVariant value, option.values)
                params.insert(option.canonicalName, value);
        }
    }
    return params;
}

void QxtCommandOptions::parse(QStringList params) {
    qxt_d().parse(params);
    qxt_d().parsed = true;
}

void QxtCommandOptionsPrivate::setOption(QxtCommandOption* option, const QString& value) {
    if(groups.contains(option->group)) {
        QList<QxtCommandOption*>& others = groups[option->group];
        foreach(QxtCommandOption* other, others) {
            if(other != option) other->values.clear();
        }
    }
    if(!(option->paramType & QxtCommandOptions::AllowMultiple))
        option->values.clear();
    option->values.append(value);
}

void QxtCommandOptionsPrivate::parse(const QStringList& params) {
    int pos = 1;    // 0 is the application name
    int ct = params.count();
    bool endFlags = false;
    bool notUnrecognized, hasEquals;
    QString name, param, value;
    while(pos < ct) {
        pos += isQtOption(params[pos]);
        param = params[pos];
        pos++;
        if(!endFlags && ((flagStyle == QxtCommandOptions::Slash && param[0] != '/') ||
                         (flagStyle != QxtCommandOptions::Slash && param[0] == '-'))) {
            // tagged argument
            if(param.length() == 1) {
                // "-" or "/" can't possibly match a flag, so use positional.
                positional.append(param);
                continue;
            }
            notUnrecognized = false;

            if(flagStyle != QxtCommandOptions::Slash && param == "--") {
                endFlags = true;
            } else if(flagStyle == QxtCommandOptions::DoubleDash && param[1] != '-') {
                int len = param.length();
                QxtCommandOption* option;
                for(int i = 1; i < len; i++) {
                    QString ch(param[i]);
                    if(ch == "-") {
                        endFlags = true;
                    } else {
                        option = lookup.value(ch, 0);
                        if(!option) {
                            // single-letter flag has no known equivalent
                            unrecognized.append(QString("-") + param[i]);
                        } else {
                            if(option->paramType & QxtCommandOptions::Required) {
                                if(pos + 1 >= params.count()) {
                                    missingParams.append(param);
                                    break;
                                }
                                value = params[pos];
                            } else {
                                value = "";
                            }
                            setOption(option);
                        }
                    }
                }
            } else {
                if(param.indexOf('=') != -1) {
                    value = param.section('=', 1);
                    param = param.section('=', 0, 0);
                    hasEquals = true;
                } else {
                    value = "";
                    hasEquals = false;
                }

                if(flagStyle == QxtCommandOptions::DoubleDash)
                    name = param.mid(2);
                else
                    name = param.mid(1);

                QxtCommandOption* option = lookup.value(name, 0);
                if(!option) {
                    unrecognized.append(param);
                } else {
                    if(option->paramType & QxtCommandOptions::Required && !hasEquals) {
                        if(pos + 1 > params.count()) {
                            missingParams.append(param);
                            break;
                        }
                        value = params[pos];
                        pos++;
                    }
                    setOption(option, value);
                }
            }
        } else {
            // positional argument
            positional.append(param);
        }
    }
}

bool QxtCommandOptions::showUnrecognizedWarning(QIODevice* device) const {
    if(!device) {
        QTextStream stream(stderr);
        return showUnrecognizedWarning(*&stream);
    } else {
        QTextStream stream(device);
        return showUnrecognizedWarning(*&stream);
    }
}

QString QxtCommandOptions::getUnrecognizedWarning() const {
    QString usage;
    QTextStream stream(&usage);
    showUnrecognizedWarning(*&stream);
    return usage;
}

bool QxtCommandOptions::showUnrecognizedWarning(QTextStream& stream) const {
    if(!qxt_d().unrecognized.count() && !qxt_d().missingParams.count()) return false;
        
    QString name;
    if(QCoreApplication::instance())
        name = QCoreApplication::applicationName();
    if(name.isEmpty())
        name = "QxtCommandOptions";
    
    if(qxt_d().unrecognized.count())
        stream << name << ": " << tr("unrecognized parameters: ") << qxt_d().unrecognized.join(" ") << endl;

    foreach(QString param, qxt_d().missingParams)
        stream << name << ": " << tr("%1 requires a parameter").arg(param) << endl;

    return true;
}

void QxtCommandOptions::showUsage(bool showQtOptions, QIODevice* device) const {
    if(!device) {
        QTextStream stream(stdout);
        showUsage(showQtOptions, *&stream);
    } else {
        QTextStream stream(device);
        showUsage(showQtOptions, *&stream);
    }
}

QString QxtCommandOptions::getUsage(bool showQtOptions) const {
    QString usage;
    QTextStream stream(&usage);
    showUsage(showQtOptions, *&stream);
    return usage;
}

void QxtCommandOptions::showUsage(bool showQtOptions, QTextStream& stream) const {
    QStringList names;
    QStringList descs;
    int maxNameLength = 0;
    QString name;

    foreach(const QxtCommandOption& option, qxt_d().options) {
        // Don't generate usage for undocumented parameters
        if(option.paramType & Undocumented) continue;

        foreach(QString n, option.names) {
            if(name.length()) name += ", ";
            if(qxt_d().flagStyle == Slash)
                name += "/";
            else if(qxt_d().flagStyle == DoubleDash && n.length() > 1)
                name += "--";
            else
                name += "-";
            name += n;
            if(option.paramType & (Optional | Required)) {
                if(option.paramType & Optional)
                    name += "[=x]";
                else if(qxt_d().paramStyle == SpaceAndEquals)
                    name += "[=]x";
                else if(qxt_d().paramStyle == Equals)
                    name += "=x";
                else
                    name += " x";
            }
        }

        // The maximum name length is used for formatting the output columns
        if(name.length() > maxNameLength)
            maxNameLength = name.length();
        names.append(name);
        descs.append(option.desc);
        name = "";
    }

    if(showQtOptions) {
        // Add a section header
        names.append(QString());
        descs.append("Common Qt Options");
        
        // Parse through qxt_qt_options
        const char* option;
        bool optionHasValue;
        for(int i = 0; qxt_qt_options[i]; i += 2) {
            option = qxt_qt_options[i];
            
            if(option[0] == '=') {
                // The option takes a parameter
                optionHasValue = true;
                option = option + 1; // pointer math to skip the =
            } else {
                optionHasValue = false;
            }

            // Concatenate on the option alias
            if(!name.isEmpty()) name += ", ";
            name += "-";
            name += option;
            if(optionHasValue) name += "[=]x";

            if(qxt_qt_options[i+1][0] != 0) {
                // The last alias for the option has the description
                if(name.length() > maxNameLength)
                    maxNameLength = name.length();
                names.append(name);
                descs.append(qxt_qt_options[i+1]);
                name = "";
            }
        }
    }

    int ct = names.count();
    QString line, wrap(maxNameLength + 3, ' ');
    for(int i = 0; i < ct; i++) {
        if(names[i].isEmpty()) {  
            // Section headers have no name entry
            stream << endl << descs[i] << ":" << endl;
            continue;
        }
        line = " " + names[i] + QString(maxNameLength - names[i].length() + 2, ' ');
        foreach(QString word, descs[i].split(' ', QString::SkipEmptyParts)) {
            if(line.length() + word.length() >= qxt_d().screenWidth) {
                stream << line << endl;
                line = wrap;
            }
            line += word + " ";
        }
        stream << line << endl;
    }
}
