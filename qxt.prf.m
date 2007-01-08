

isEmpty(QXTbase){
unix : QXTbase=/opt/qxt
win32: QXTbase=C:/libqxt
macx :
}
isEmpty(QXTinclude){
unix : QXTinclude=/usr/include
win32: QXTinclude=$${QXTbase}/src
macx :
}
isEmpty(QXTbin){
unix : QXTbin=/usr/lib
win32: QXTbin=$${QXTbase}/bin
macx :
}



INCLUDEPATH+=$${QXTinclude}
LIBS += -Wl,-rpath,$${QXTbin} -L$${QXTbin}


contains(QXT, kit ){
        INCLUDEPATH +=$${QXTinclude}/kit
	LIBS += -lQxtKit
	QXT+=core
        }
contains(QXT, gui ){
        INCLUDEPATH +=$${QXTinclude}/gui
	LIBS += -lQxtGui
	QXT+=core
        }
contains(QXT, network ){
        INCLUDEPATH +=$${QXTinclude}/network
	LIBS += -lQxtNetwork
	QXT+=core
        }
contains(QXT, sql ){
        INCLUDEPATH +=$${QXTinclude}/sql
	LIBS += -lQxtSql
	QXT+=core
        }
contains(QXT, media ){
        INCLUDEPATH +=$${QXTinclude}/media
	LIBS += -lQxtMedia
	QXT+=core
        }
contains(QXT, core ){
        INCLUDEPATH +=$${QXTinclude}/core
	LIBS += -lQxtCore
        }
