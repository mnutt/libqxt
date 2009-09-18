SUBDIRS += tools/3rdparty/qdoc3

win32:!win32-g++ {
    unixstyle = false
} else :win32-g++:isEmpty(QMAKE_SH) {
    unixstyle = false
} else {
    unixstyle = true
}

$$unixstyle {
    QDOC = QXT_SOURCE_TREE=$$QXT_SOURCE_TREE QXT_BUILD_TREE=$$QXT_BUILD_TREE $$QXT_BUILD_TREE/tools/3rdparty/qdoc3/qdoc3
} else {
    QDOC = set QXT_SOURCE_TREE=$$QXT_SOURCE_TREE&& set QXT_BUILD_TREE=$$QXT_BUILD_TREE&& $$QXT_BUILD_TREE/tools/3rdparty/qdoc3/qdoc3.exe
    QDOC = $$replace(QDOC, "/", "\\\\")
}

adp_docs.commands = ($$QDOC -DQXT_DOXYGEN_RUN $$QXT_SOURCE_TREE/doc/src/qxt.qdocconf)
adp_docs.depends += sub-tools-3rdparty-qdoc3
docs.depends = adp_docs
QMAKE_EXTRA_TARGETS += adp_docs docs

htmldocs.files = $$QXT_BUILD_TREE/doc/html
htmldocs.path = $$QXT_INSTALL_DOCS
htmldocs.CONFIG += no_check_exist

#qchdocs.files= $$QXT_BUILD_TREE/doc/qch
#qchdocs.path = $$QXT_INSTALL_DOCS
#qchdocs.CONFIG += no_check_exist
INSTALLS += htmldocs # qchdocs
