CONFIG += qtestlib
CONFIG -= app_bundle

INCLUDEPATH     += $$QXT_SOURCE_TREE/include/
unix:!macx:LIBS += -Wl,-rpath,$$QXT_BUILD_TREE/lib
macx:LIBS       += -F$$QXT_BUILD_TREE/lib
LIBS            += -L$$QXT_BUILD_TREE/lib

defineTest(qxtAddTestModule) {
    INCLUDEPATH       += $$QXT_SOURCE_TREE/src/$$1
    INCLUDEPATH       += $$QXT_SOURCE_TREE/include/$$2
    qtAddLibrary($$2)
}
contains(QXT, berkeley) {
    qxtAddTestModule(berkeley, QxtBerkeley)
    QXT += core
}
contains(QXT, web) {
    qxtAddTestModule(web, QxtWeb)
    QXT += core network
    QT  += network
}
contains(QXT, gui) {
    qxtAddTestModule(gui, QxtGui)
    QXT += core
    QT  += gui
}
contains(QXT, network) {
    qxtAddTestModule(network, QxtNetwork)
    QXT += core
    QT  += network
}
contains(QXT, sql) {
    qxtAddTestModule(sql, QxtSql)
    QXT += core
    QT  += sql
}
contains(QXT, core) {
    qxtAddTestModule(core, QxtCore)
}

DEPENDPATH  += $$INCLUDEPATH

test.depends = first
!isEmpty(DESTDIR):test.commands += cd $(DESTDIR) &&
unix {
    test.commands += ./$(TARGET)
} else:win32 {
    DESTDIR = ./
    test.CONFIG += recursive
    build_pass:test.commands += $(TARGET)
}
QMAKE_EXTRA_TARGETS += test
