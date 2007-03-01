                                                            
                                                                    
                                                                    
                                                                               







#keep the space lines above. nsis needs them, as it can only override bytes

isEmpty(QXTbase){
unix : QXTbase=/usr
win32: QXTbase=C:/libqxt
macx :
}

isEmpty(QXTlib):	QXTlib=$${QXTbase}/lib
isEmpty(QXTinclude):	QXTinclude=$${QXTbase}/include/Qxt/
isEmpty(QXTbin):	QXTbin=$${QXTbase}/lib




INCLUDEPATH+=$${QXTinclude}
LIBS += -Wl,-rpath,$${QXTlib} -L$${QXTlib}


contains(QXT, curses ){
        INCLUDEPATH +=$${QXTinclude}/QxtCurses
	LIBS += -lQxtCurses
	QXT+=kit
        }
contains(QXT, gui ){
        INCLUDEPATH +=$${QXTinclude}/QxtGui
	LIBS += -lQxtGui
	QXT+=kit
        }
contains(QXT, network ){
        INCLUDEPATH +=$${QXTinclude}/QxtNetwork
	LIBS += -lQxtNetwork
	QXT+=kit
        }
contains(QXT, sql ){
        INCLUDEPATH +=$${QXTinclude}/QxtSql
	LIBS += -lQxtSql
	QXT+=kit
        }
contains(QXT, media ){
        INCLUDEPATH +=$${QXTinclude}/QxtMedia
	LIBS += -lQxtMedia
	QXT+=kit
        }
contains(QXT, kit ){
        INCLUDEPATH +=$${QXTinclude}/QxtKit
	LIBS += -lQxtKit
	QXT+=core
        }
contains(QXT, core ){
        INCLUDEPATH +=$${QXTinclude}/QxtCore
	LIBS += -lQxtCore
        }
