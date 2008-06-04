HEADERS  += qxtcrypto.h
HEADERS  += qxthash.h
HEADERS  += qxthmac.h

SOURCES  += qxthash.cpp
SOURCES  += qxthmac.cpp
SOURCES  += thirdparty/md5.cpp
SOURCES  += thirdparty/md4.cpp

contains(DEFINES,HAVE_OPENSSL){
    HEADERS += qxtblowfish.h
    SOURCES += qxtblowfish.cpp
    !win32:LIBS    += -lcrypto
}
