INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += qxtjsonrpccall.h
HEADERS += qxtjsonrpcclient.h
HEADERS += qxtnetwork.h
HEADERS += qxtmail_p.h
HEADERS += qxtsmtp.h
HEADERS += qxtsmtp_p.h
HEADERS += qxtmailattachment.h
HEADERS += qxtmailmessage.h
HEADERS += qxtrpcpeer.h
HEADERS += qxttcpconnectionmanager.h
HEADERS += qxttcpconnectionmanager_p.h
HEADERS += qxtxmlrpccall.h
HEADERS += qxtxmlrpcclient.h
HEADERS += qxtxmlrpc_p.h
HEADERS += qxtpop3.h
HEADERS += qxtpop3_p.h
HEADERS += qxtpop3reply.h
HEADERS += qxtpop3reply_p.h
HEADERS += qxtpop3statreply.h
HEADERS += qxtpop3listreply.h
HEADERS += qxtpop3retrreply.h
HEADERS += qxtsslserver.h
HEADERS += qxtsslconnectionmanager.h

SOURCES += qxtjsonrpccall.cpp
SOURCES += qxtjsonrpcclient.cpp
SOURCES += qxtmailattachment.cpp
SOURCES += qxtmailmessage.cpp
SOURCES += qxtrpcpeer.cpp
SOURCES += qxtsmtp.cpp
SOURCES += qxttcpconnectionmanager.cpp
SOURCES += qxtxmlrpccall.cpp
SOURCES += qxtxmlrpcclient.cpp
SOURCES += qxtxmlrpc_p.cpp
SOURCES += qxtpop3.cpp
SOURCES += qxtpop3reply.cpp
SOURCES += qxtsslserver.cpp
SOURCES += qxtsslconnectionmanager.cpp

contains(DEFINES,HAVE_OPENSSL){
 HEADERS += qxtsshchannel.h
 HEADERS += qxtsshchannel_p.h
 HEADERS += qxtsshclient.h
 HEADERS += qxtsshclient_p.h
 HEADERS += qxtsshprocess.h
 HEADERS += qxtsshtcpsocket.h

 SOURCES += qxtsshchannel.cpp
 SOURCES += qxtsshclient.cpp
 SOURCES += qxtsshprocess.cpp
 SOURCES += qxtsshtcpsocket.cpp	
}

