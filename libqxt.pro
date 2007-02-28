#
#
#
#
#
#
#      !!!!!
#
#      keep your hands of
#      configuration is in config.pro 
#
#      !!!!!
#
#
#
#
#
#
#
#
include (config.pri)
include (features/install.pri)

TEMPLATE = subdirs




docs.files = deploy/docs/*
docs.path = $${QXTINSTALLDIR}/docs


qxtincludes.path = $${include.path}/Qxt
qxtincludes.files= deploy/include/Qxt/*



#write the paths to prf file
unix:system((echo QXTbase=$${QXTINSTALLDIR}; echo QXTinclude=$${include.path}; echo QXTbin=$${bin.path}; echo QXTlib=$${lib.path}; cat deploy/qt/qxt.prf.m) > deploy/qt/qxt.prf)

#windows supports similar syntax
win32:system((echo QXTbase=$${QXTINSTALLDIR}& echo QXTinclude=$${include.path} & echo QXTbin=$${bin.path} & echo QXTlib=$${lib.path} & type deploy\qt\qxt.prf.m) > deploy\qt\qxt.prf)





features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/*.prf	








INSTALLS = docs qxtincludes features 




contains( QXT_BUILD, core ){
        message( building the core )
        SUBDIRS += src/core	
        }

contains( QXT_BUILD, kit ){
        message( building kit module )
        SUBDIRS += src/kit
        }

contains( QXT_BUILD, gui ){
        message( building gui module )
        SUBDIRS += src/gui
        SUBDIRS += src/designer
        }

contains( QXT_BUILD, network ){
        message( building network module )
        SUBDIRS += src/network
        }

contains( QXT_BUILD, sql ){
        message( building sql module )
        SUBDIRS += src/sql
        }

contains( QXT_BUILD, media ){
        message( building media module )
        SUBDIRS += src/media
        }

contains( QXT_BUILD, curses ){
        message( building curses module )
        SUBDIRS += src/curses
        }




