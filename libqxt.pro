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
include (install.pri)

TEMPLATE = subdirs




docs.files = deploy/docs/*

qxtincludes.path = $${include.path}/Qxt
qxtincludes.files= deploy/include/Qxt/*





	bin.files =


#write the paths to prf file
unix :system((echo QXTbase=$${QXTINSTALLDIR}; echo QXTinclude=$${include.path}; echo QXTbin=$${bin.path}; echo QXTlib=$${lib.path}; cat deploy/qt/qxt.prf.m) > deploy/qt/qxt.prf)
win32:system(move deploy/qt/qxt.prf.m deploy/qt/qxt.prf)  #TODO HANDLE IT!





features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/*.prf	








INSTALLS = docs bin qxtincludes features 




contains( QXT_BUILD, core ){
        message( building the core )
        SUBDIRS += src/core	
	core.files +=  deploy/include/QxtCore/*
	core.path  =  $${include.path}/QxtCore
	INSTALLS += core
        }

contains( QXT_BUILD, kit ){
        message( building kit module )
        SUBDIRS += src/kit
	kit.files +=  deploy/include/QxtKit/*
	kit.path  =  $${include.path}/QxtKit
	INSTALLS += kit
        }

contains( QXT_BUILD, gui ){
        message( building gui module )
        SUBDIRS += src/gui
	gui.files +=  deploy/include/QxtGui/*
	gui.path  =  $${include.path}/QxtGui
	INSTALLS += gui


        SUBDIRS += designer
	designer.path = $$[QT_INSTALL_PLUGINS]/designer
	designer.files = designer/libQxtDesignerPlugins.*
	INSTALLS += designer
        }

contains( QXT_BUILD, network ){
        message( building network module )
        SUBDIRS += src/network
	network.files +=  deploy/include/QxtNetwork/*
	network.path  =  $${include.path}/QxtNetwork
	INSTALLS += network
        }

contains( QXT_BUILD, sql ){
        message( building sql module )
        SUBDIRS += src/sql
	sql.files +=  deploy/include/QxtSql/*
	sql.path  =  $${include.path}/QxtSql
	INSTALLS += sql
        }

contains( QXT, media ){
        message( building media module )
        SUBDIRS += src/media
	media.files +=  deploy/include/QxtMedia/*	
	media.path  =  $${include.path}/QxtMedia
	INSTALLS += media
        }

contains( QXT_BUILD, curses ){
        message( building curses module )
        SUBDIRS += src/curses
	curses.files +=  deploy/include/QxtCurses/*	
	curses.path  =  $${include.path}/QxtCurses
	INSTALLS += curses
        }

# contains( QXT_BUILD, mox ){
#         message( building mox )
#         SUBDIRS += mox
# 	unix:mox.files +=  deploy/bin/mox
# 	win32:mox.files += deploy/bin/mox.exe
# 	mox.path  =  $${bin.path}
# 	INSTALLS += mox
#         }




