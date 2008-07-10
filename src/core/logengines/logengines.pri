INCLUDEPATH += logengines/

# interfaces
HEADERS += logengines/qxtabstractfileloggerengine.h 
SOURCES += logengines/qxtabstractfileloggerengine.cpp 

# Basic STD Logger Engine
HEADERS += logengines/qxtbasicstdloggerengine.h
SOURCES += logengines/qxtbasicstdloggerengine.cpp

# Basic File Logger Engine
HEADERS += logengines/qxtbasicfileloggerengine.h
SOURCES += logengines/qxtbasicfileloggerengine.cpp

# XML File Logger Engine
HEADERS += logengines/qxtxmlfileloggerengine.h
SOURCES += logengines/qxtxmlfileloggerengine.cpp
