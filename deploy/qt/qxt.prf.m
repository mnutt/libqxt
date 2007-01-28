                                                            
                                                                    
                                                                    
                                                                               
#keep the space lines above. nsis needs them

isEmpty(QXTbase){
unix : QXTbase=/usr
win32: QXTbase=C:/libqxt
macx :
}

isEmpty(QXTlib):	QXTlib=$${QXTbase}/lib
isEmpty(QXTinclude):	QXTinclude=$${QXTbase}/include
isEmpty(QXTbin):	QXTbin=$${QXTbase}/lib




INCLUDEPATH+=$${QXTinclude}
LIBS += -Wl,-rpath,$${QXTlib} -L$${QXTlib}


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
