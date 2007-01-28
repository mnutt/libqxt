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
TEMPLATE = subdirs



unix :  docs.path = $${QXTINSTALLDIR}/doc/libqxt
win32:  docs.path = $${QXTINSTALLDIR}/docs
macx :  docs.path = $${QXTINSTALLDIR}/docs
        docs.files = deploy/docs/*


unix :	lib.path = $${QXTINSTALLDIR}/lib
win32:	lib.path = $${QXTINSTALLDIR}/lib
macx :	lib.path = $${QXTINSTALLDIR}/lib
      	lib.files = deploy/libs/*


unix :	include.path = $${QXTINSTALLDIR}/include/qxt
win32:	include.path = $${QXTINSTALLDIR}/include
macx :	include.path =  $${QXTINSTALLDIR}/include
	include.files = src/QxtDefines.h  src/Qxt.h

unix :	bin.path  = $${QXTINSTALLDIR}/bin
win32:	bin.path  = $${QXTINSTALLDIR}/bin
macx :	bin.path  =  $${QXTINSTALLDIR}/bin
	bin.files =


#write the paths to prf file
unix :system((echo QXTbase=$${QXTINSTALLDIR}; echo QXTinclude=$${include.path}; echo QXTbin=$${bin.path}; echo QXTlib=$${lib.path}; cat deploy/qt/qxt.prf.m) > deploy/qt/qxt.prf)
win32:system(move deploy/qt/qxt.prf.m deploy/qt/qxt.prf)  #TODO HANDLE IT!





features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/*.prf	








INSTALLS = lib docs bin include features 




contains( QXT, core ){
        message( building the core )
        SUBDIRS += src/core	
	core.files +=  src/core/*.h
	core.files +=  deploy/include/core/*
	core.path  =  $${include.path}/core
	INSTALLS += core
        }

contains( QXT, kit ){
        message( building kit module )
        SUBDIRS += src/kit
	kit.files +=  src/kit/*.h
	kit.files +=  deploy/include/kit/*
	kit.path  =  $${include.path}/kit
	INSTALLS += kit
        }

contains( QXT, gui ){
        message( building gui module )
        SUBDIRS += src/gui
	gui.files +=  src/gui/*.h
	gui.files +=  deploy/include/gui/*
	gui.path  =  $${include.path}/gui
	INSTALLS += gui


        SUBDIRS += designer
	designer.path = $$[QT_INSTALL_PLUGINS]/designer
	designer.files = designer/libQxtDesignerPlugins.*
	INSTALLS += designer
        }

contains( QXT, network ){
        message( building network module )
        SUBDIRS += src/network
	network.files +=  src/network/*.h
	network.files +=  deploy/include/network/*
	network.path  =  $${include.path}/network
	INSTALLS += network
        }

contains( QXT, sql ){
        message( building sql module )
        SUBDIRS += src/sql
	sql.files +=  src/sql/*.h
	sql.files +=  deploy/include/sql/*
	sql.path  =  $${include.path}/sql
	INSTALLS += sql
        }

contains( QXT, media ){
        message( building media module )
        SUBDIRS += src/media
	media.files +=  src/media/*.h
	media.files +=  deploy/include/media/*	
	media.path  =  $${include.path}/media
	INSTALLS += media
        }

contains( QXT, mox ){
        message( building mox )
        SUBDIRS += mox
	unix:mox.files +=  deploy/bin/mox
	win32:mox.files += deploy/bin/mox.exe
	mox.path  =  $${bin.path}
	INSTALLS += mox
        }




