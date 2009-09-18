CONFIG += qtestlib
CONFIG -= app_bundle

include($$QXT_SOURCE_TREE/src/qxtlibs.pri)

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
