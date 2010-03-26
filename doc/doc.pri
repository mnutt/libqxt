SUBDIRS += tools/3rdparty/qdoc3

win32 {
    QXT_WINCONFIG = release/
    !CONFIG(release, debug|release) {
        QXT_WINCONFIG = debug/
    }
}

win32:!win32-g++ {
    unixstyle = false
} else :win32-g++:isEmpty(QMAKE_SH) {
    unixstyle = false
} else {
    unixstyle = true
}

$$unixstyle {
    QDOC = QXT_SOURCE_TREE=$$QXT_SOURCE_TREE QXT_BUILD_TREE=$$QXT_BUILD_TREE $$QXT_BUILD_TREE/tools/3rdparty/qdoc3/$${QXT_WINCONFIG}qdoc3
} else {
    QDOC = set QXT_SOURCE_TREE=$$QXT_SOURCE_TREE&& set QXT_BUILD_TREE=$$QXT_BUILD_TREE&& $$QXT_BUILD_TREE/tools/3rdparty/qdoc3/$${QXT_WINCONFIG}qdoc3.exe
    QDOC = $$replace(QDOC, "/", "\\\\")
}

adp_docs.commands = ($$QDOC -DQXT_DOXYGEN_RUN $$QXT_SOURCE_TREE/doc/src/qxt.qdocconf)
adp_docs.depends += sub-tools-3rdparty-qdoc3
docs.depends = adp_docs
QMAKE_EXTRA_TARGETS += adp_docs docs

htmldocs.files = $$QXT_BUILD_TREE/doc/html/*
htmldocs.path = $$QXT_INSTALL_DOCS
htmldocs.CONFIG += no_check_exist

INSTALLS += htmldocs

exists( $$[QT_INSTALL_BINS]/qhelpgenerator) {
    QHELPGENERATOR = $$[QT_INSTALL_BINS]/qhelpgenerator
    qch_docs.commands = $$QHELPGENERATOR  $$QXT_BUILD_TREE/doc/html/qxt.qhp -o $$QXT_BUILD_TREE/doc/qch/qxt.qch
    qch_docs.depends = adp_docs
    docs.depends += qch_docs
    QMAKE_EXTRA_TARGETS += qch_docs
    qchdocs.files= $$QXT_BUILD_TREE/doc/qch/qxt.qch
    qchdocs.path = $$QXT_INSTALL_DOCS
    qchdocs.CONFIG += no_check_exist
    INSTALLS += qchdocs
}
