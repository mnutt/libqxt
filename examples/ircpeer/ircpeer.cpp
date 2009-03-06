#include "ircpeer.h"
#include <QRegExp>

IRCSerializer::IRCSerializer() : QxtAbstractSignalSerializer() {
    qRegisterMetaType<IRCName>();
}

bool IRCSerializer::canDeserialize(const QByteArray& buffer) const {
    return buffer.indexOf('\n') != -1 || buffer.indexOf('\r') != -1;
}

static bool serializeParam(QTextStream& str, QVariant p) {
    if(!p.isValid() || !p.canConvert(QVariant::ByteArray)) {
        str << "\r\n" << flush;
        return true;
    }
    QByteArray ba = p.toByteArray();
    if(ba.contains(' ') || ba[0] == ':') 
    {
        str << " :" << ba << "\r\n" << flush;
        return true;
    }
    str << " " << ba << flush;
    return false;
}

QByteArray IRCSerializer::serialize(const QString& fn, const QVariant& p1, const QVariant& p2, const QVariant& p3,
                                    const QVariant& p4, const QVariant& p5, const QVariant& p6, const QVariant& p7, const QVariant& p8) const {
    if(fn == "raw") return p1.toString().toUtf8() + "\r\n";
    QByteArray rv;
    QTextStream str(&rv);
    if(p1.isValid()) {
        if(p1.canConvert<IRCName>()) {
            QByteArray name = p1.value<IRCName>().assemble();
            if(!name.isEmpty())
                str << ":" << p1.value<IRCName>().assemble() << " ";
            
        } else if(!p1.toByteArray().isEmpty()) {
            str << ":" << p1.toByteArray() << " ";
        }
    }
    str << fn << flush;

    if(serializeParam(str, p2)) return rv;
    if(serializeParam(str, p3)) return rv;
    if(serializeParam(str, p4)) return rv;
    if(serializeParam(str, p5)) return rv;
    if(serializeParam(str, p6)) return rv;
    if(serializeParam(str, p7)) return rv;
    if(serializeParam(str, p8)) return rv;
    return rv + "\r\n";
}

QPair<QString, QList<QVariant> > IRCSerializer::deserialize(QByteArray& data) {
    int lfPos = data.indexOf('\n'), crPos = data.indexOf('\r'), wordPos = 0, endPos = (crPos == -1 || lfPos < crPos) ? lfPos : crPos;
    QByteArray message = data.left(endPos).trimmed(), prefix;
    data = data.mid(endPos+1);
    if(message.isEmpty()) return qMakePair(QString(), QList<QVariant>());

    QList<QByteArray> words = message.split(' ');
    if(words[0][0] == ':') {
        prefix = words[0].mid(1);
        while(wordPos < words.count() && words[wordPos++].isEmpty()) 
            return qMakePair(QString(), QList<QVariant>() << QVariant());
    }

    QString command(words[wordPos]);
    QList<QVariant> params;
    int cmdNum = command.toInt();
    if(cmdNum != 0) {
        params << QVariant::fromValue(IRCName((prefix + ':' + command).toUtf8(), "", prefix));
        command = "numeric";
    } else {
        if(prefix.isEmpty())          params << QVariant::fromValue(IRCName("","",""));
        else if(prefix.contains('@')) params << QVariant::fromValue(IRCName::fromName(prefix));
        else                          params << QVariant::fromValue(IRCName(prefix, prefix, prefix));
    }

    while(wordPos++ < words.count()-1) {
        if(words[wordPos].isEmpty()) continue;
        if(words[wordPos][0] == ':') {
            QByteArray trailing = words[wordPos++].mid(1);
            while(wordPos < words.count()) 
                trailing = trailing + ' ' + words[wordPos++];
            params << trailing;
            break;
        }
        params << words[wordPos];
    }

    if(command == "numeric") {
        params.removeAt(1);                     // always your own nick
        while(params[1].toByteArray() == "=" || params[1].toByteArray() == "@")
            params.removeAt(1);                 // nothing important
        if(params.size() == 2) {
            params.push_front(QByteArray());    // make it show up in the system window
            params.swap(0, 1);
        } else if(cmdNum < 300 || params.size() > 3) {  // some numeric responses aren't a single string
            QList<QVariant> newparams;
            newparams << params[0];
            int i;
            if(cmdNum < 300) {
                newparams << QByteArray();
                i = 1;
            } else {
                newparams << params[1];
                i = 2;
            }
            QByteArray ba;
            for(; i < params.count(); i++) ba += params[i].toByteArray() + ' ';
            newparams << ba;
            params = newparams;
        }
    } else if(command == "PRIVMSG") {
        QByteArray p2 = params[2].toByteArray();
        if(p2.size() > 0 && p2[0] == '\001') {
            message = p2.replace("\001", "");
            int spacePos = message.indexOf(' ');
            if(spacePos == -1) spacePos = message.size();
            command = "CTCP-"+message.left(spacePos);
            params[2] = message.mid(spacePos);
        }
    } else if(command == "NOTICE" && params[0].isNull()) {
        params[0] = QVariant::fromValue(IRCName(params[1].toByteArray(), "", params[1].toByteArray()));
    }

    return qMakePair(command, params);
}

IRCName IRCName::fromName(const QByteArray& name) {
    QRegExp re("([^@!]*)(?:!([^@]*)?)(?:@(.*))?");
    re.exactMatch(QString::fromUtf8(name.data()));
    return IRCName(re.cap(1).toUtf8(), re.cap(2).toUtf8(), re.cap(3).toUtf8());
}

IRCName::IRCName(QByteArray nick, QByteArray ident, QByteArray host) : nick(nick), ident(ident), host(host) {}

QByteArray IRCName::assemble() const {
    return nick + (ident.isEmpty() ? QByteArray() : '!' + ident) + (host.isEmpty() ? QByteArray() : '@' + host);
}
