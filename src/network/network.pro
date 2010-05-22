CLEAN_TARGET     = QxtNetwork
DEFINES         += BUILD_QXT_NETWORK
QT               = core network
QXT              = core
CONVENIENCE     += $$CLEAN_TARGET

include(network.pri)
include(../qxtbase.pri)

contains(DEFINES,HAVE_OPENSSL){
 include(../3rdparty/libssh2/libssh2.pri)
}
