HEADERS += qxtdiscoverableservice.h
HEADERS += qxtdiscoverableservice_p.h
HEADERS += qxtservicebrowser.h
HEADERS += qxtservicebrowser_p.h
HEADERS += qxtdiscoverableservicename.h

SOURCES += qxtdiscoverableservice.cpp
SOURCES += qxtservicebrowser.cpp
SOURCES += qxtdiscoverableservicename.cpp

unix:!macx {
DEFINES += USE_AVAHI
SOURCES += qxtmdns_avahi.cpp
HEADERS += qxtmdns_avahi.h
} else {
SOURCES += qxtmdns_bonjour.cpp
HEADERS += qxtmdns_bonjour.h
}
