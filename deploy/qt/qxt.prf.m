                                                            
                                                                    
                                                                    
                                                                               







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
	unix : LIBS += -lQxtCurses
	win32: LIBS += -lQxtCurses0
	QXT+=kit
        }
contains(QXT, gui ){
        INCLUDEPATH +=$${QXTinclude}/QxtGui
	unix : LIBS += -lQxtGui
	win32: LIBS += -lQxtGui0
	QXT+=kit
        }
contains(QXT, network ){
        INCLUDEPATH +=$${QXTinclude}/QxtNetwork
	unix : LIBS += -lQxtNetwork
	win32: LIBS += -lQxtNetwork0
	QXT+=kit
        }
contains(QXT, sql ){
        INCLUDEPATH +=$${QXTinclude}/QxtSql
	unix : LIBS += -lQxtSql
	win32: LIBS += -lQxtSql0
	QXT+=kit
        }
contains(QXT, media ){
        INCLUDEPATH +=$${QXTinclude}/QxtMedia
	LIBS += -lQxtMedia
	QXT+=kit
        }
contains(QXT, kit ){
        INCLUDEPATH +=$${QXTinclude}/QxtKit
	unix : LIBS += -lQxtKit
	win32: LIBS += -lQxtKit0
	QXT+=core
        }
contains(QXT, core ){
        INCLUDEPATH +=$${QXTinclude}/QxtCore
	unix : LIBS += -lQxtCore
	win32: LIBS += -lQxtCore
        }
