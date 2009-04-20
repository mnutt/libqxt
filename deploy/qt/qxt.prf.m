                                                            
                                                                    
                                                                    
                                                                               







#keep the space lines above. nsis needs them, as it can only override bytes

isEmpty(QXTbase){
    unix:!macx: QXTbase = /usr/local/Qxt
    win32:      QXTbase = C:/libqxt
    macx :
}

isEmpty(QXTinclude): QXTinclude = $${QXTbase}/include/Qxt/
isEmpty(QXTbin):     QXTbin     = $${QXTbase}/bin

macx {
    isEmpty(QXTlib):     QXTlib = /Library/Frameworks
}

!macx {
    isEmpty(QXTlib):     QXTlib = $${QXTbase}/lib
}

INCLUDEPATH     += $${QXTinclude}
unix:!macx:LIBS += -Wl,-rpath,$${QXTlib}
macx:LIBS       += -F$${QXTlib}
LIBS            += -L$${QXTlib}


contains(QXT, berkeley) {
    INCLUDEPATH       += $${QXTinclude}/QxtBerkeley
    macx: INCLUDEPATH += $${QXTlib}//QxtBerkeley.framework/HEADERS/
    qtAddLibrary(QxtBerkeley)
    QXT += core
    contains(QXT_MODULES, berkeley):DEFINES += QXT_BERKELEY_LIB
}
contains(QXT, crypto) {
    INCLUDEPATH       += $${QXTinclude}/QxtCrypto
    macx: INCLUDEPATH += $${QXTlib}/QxtCrypto.framework/HEADERS/
    qtAddLibrary(QxtCrypto)
    QXT += core
    contains(QXT_MODULES, crypto):DEFINES += QXT_CRYPTO_LIB
}
contains(QXT, web) {
    INCLUDEPATH       += $${QXTinclude}/QxtWeb
    macx: INCLUDEPATH += $${QXTlib}/QxtWeb.framework/HEADERS/
    qtAddLibrary(QxtWeb)
    QXT += core network
    QT  += network
    contains(QXT_MODULES, web):DEFINES += QXT_WEB_LIB
}
contains(QXT, gui) {
    INCLUDEPATH       += $${QXTinclude}/QxtGui
    macx: INCLUDEPATH += $${QXTlib}/QxtGui.framework/HEADERS/
    qtAddLibrary(QxtGui)
    QXT += core
    QT  += gui
    contains(QXT_MODULES, gui):DEFINES += QXT_GUI_LIB
}
contains(QXT, zeroconf) {
    INCLUDEPATH       += $${QXTinclude}/QxtZeroconf
    macx: INCLUDEPATH += $${QXTlib}/QxtZeroconf.framework/HEADERS/
    qtAddLibrary(QxtZeroconf)
    QXT += core network
    QT  += network
}
contains(QXT, network) {
    INCLUDEPATH       += $${QXTinclude}/QxtNetwork
    macx: INCLUDEPATH += $${QXTlib}/QxtNetwork.framework/HEADERS/
    qtAddLibrary(QxtNetwork)
    QXT += core
    QT  += network
    contains(QXT_MODULES, network):DEFINES += QXT_NETWORK_LIB
}
contains(QXT, sql) {
    INCLUDEPATH       += $${QXTinclude}/QxtSql
    macx: INCLUDEPATH += $${QXTlib}/QxtSql.framework/HEADERS/
    qtAddLibrary(QxtSql)
    QXT += core
    QT  += sql
    contains(QXT_MODULES, sql):DEFINES += QXT_SQL_LIB
}
contains(QXT, core) {
    INCLUDEPATH       += $${QXTinclude}/QxtCore
    macx: INCLUDEPATH += $${QXTlib}/QxtCore.framework/HEADERS/
    qtAddLibrary(QxtCore)
    contains(QXT_MODULES, core):DEFINES += QXT_CORE_LIB
}
