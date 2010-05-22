INCLUDEPATH +=  $$PWD/libssh2/include \
                $$PWD/libssh2/include \
                $$PWD/libssh2/src 

SOURCES += $$PWD/libssh2/src/agent.c \
           $$PWD/libssh2/src/channel.c \
           $$PWD/libssh2/src/comp.c \
           $$PWD/libssh2/src/crypt.c \
           $$PWD/libssh2/src/global.c \
           $$PWD/libssh2/src/hostkey.c \
           $$PWD/libssh2/src/keepalive.c \
           $$PWD/libssh2/src/kex.c \
           $$PWD/libssh2/src/knownhost.c \
           $$PWD/libssh2/src/libgcrypt.c \
           $$PWD/libssh2/src/mac.c \
           $$PWD/libssh2/src/misc.c \
           $$PWD/libssh2/src/openssl.c \
           $$PWD/libssh2/src/packet.c \
           $$PWD/libssh2/src/pem.c \
           $$PWD/libssh2/src/publickey.c \
           $$PWD/libssh2/src/scp.c \
           $$PWD/libssh2/src/session.c \
           $$PWD/libssh2/src/sftp.c \
           $$PWD/libssh2/src/transport.c \
           $$PWD/libssh2/src/userauth.c \
           $$PWD/libssh2/src/version.c 


win32{
 INCLUDEPATH +=  $$PWD/libssh2/win32/
}

!win32:!symbian{
  INCLUDEPATH +=  $$PWD/linux
  LIBS+=-lcrypto
}
