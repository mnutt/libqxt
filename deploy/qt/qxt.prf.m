                                                            
                                                                    
                                                                    
                                                                               







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
}
contains(QXT, crypto) {
    INCLUDEPATH       += $${QXTinclude}/QxtCrypto
    macx: INCLUDEPATH += $${QXTlib}/QxtCrypto.framework/HEADERS/
    qtAddLibrary(QxtCrypto)
    QXT += core
}
contains(QXT, web) {
    INCLUDEPATH       += $${QXTinclude}/QxtWeb
    macx: INCLUDEPATH += $${QXTlib}/QxtWeb.framework/HEADERS/
    qtAddLibrary(QxtWeb)
    QXT += core network
    QT  += network
}
contains(QXT, gui) {
    INCLUDEPATH       += $${QXTinclude}/QxtGui
    macx: INCLUDEPATH += $${QXTlib}/QxtGui.framework/HEADERS/
    qtAddLibrary(QxtGui)
    QXT += core
    QT  += gui
}
contains(QXT, network) {
    INCLUDEPATH       += $${QXTinclude}/QxtNetwork
    macx: INCLUDEPATH += $${QXTlib}/QxtNetwork.framework/HEADERS/
    qtAddLibrary(QxtNetwork)
    QXT += core
    QT  += network
}
contains(QXT, sql) {
    INCLUDEPATH       += $${QXTinclude}/QxtSql
    macx: INCLUDEPATH += $${QXTlib}/QxtSql.framework/HEADERS/
    qtAddLibrary(QxtSql)
    QXT += core
    QT  += sql
}
contains(QXT, core) {
    INCLUDEPATH       += $${QXTinclude}/QxtCore
    macx: INCLUDEPATH += $${QXTlib}/QxtCore.framework/HEADERS/
    qtAddLibrary(QxtCore)
}
