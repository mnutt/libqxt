HEADERS  += qxtblowfish.h
HEADERS  += qxtcrypto.h
HEADERS  += qxthash.h
HEADERS  += qxthmac.h

SOURCES  += qxtblowfish.cpp
SOURCES  += qxthash.cpp
SOURCES  += qxthmac.cpp
SOURCES  += thirdparty/md5.cpp
SOURCES  += thirdparty/md4.cpp

contains(DEFINES,HAVE_OPENSSL) {
    !win32:LIBS += -lcrypto
}
