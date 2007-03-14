/*******************************************************************
Qt extended Library
Copyright (C) 2007 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

/*******************************************************************
Qt extended Library
Copyright (C) 2006 Adam Higerd and Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/


/** \defgroup core
        The Core contains naturaly  the most important parts of Qxt everything is based one. it has no QT depencies and is licenced under pure lgpl
*/

/** \defgroup kit
        the kit module contains the base parts of Qxt that depend on QtCore
*/

/** \defgroup sql
        parts that depend on QtSql (and at least QtCore)
*/

/** \defgroup network
        parts that depend on QtNetwork (and at least QtCore)
*/

/** \defgroup gui
        parts that depend on QtGui (and at least QtCore)
*/

/** \defgroup media
        special module for Media Classes
*/

/** \defgroup curses
        Qt like ncurses Frontend
*/



/**

*/
/*! \mainpage Qt extension librarys
 *
 *
 * Qxt Provides Classes for extended needs based on the Qt Library by Trolltech
 *
 * Checkout the classes list

\image html logo.png
 *
 */


#ifndef QXTDEFINES_HEADER_GUARDD
#define QXTDEFINES_HEADER_GUARDD









//--------------------------global macros------------------------------

#ifndef QXT_NO_MACROS

#endif

//--------------------------export macros------------------------------




#    define QXT_DLLEXPORT DO_NOT_USE_THIS_ANYMORE







#if defined(QXT_WINDOWS)

#	if defined(BUILD_QXT_CORE)
#   		define QXT_CORE_EXPORT __declspec(dllexport)
#	else
#   		define QXT_CORE_EXPORT __declspec(dllimport)
#	endif

#	if defined(BUILD_QXT_GUI)
#   		define QXT_GUI_EXPORT __declspec(dllexport)
#	else
#   		define QXT_GUI_EXPORT __declspec(dllimport)
#	endif

#	if defined(BUILD_QXT_KIT)
#   		define QXT_KIT_EXPORT __declspec(dllexport)
#	else
#   		define QXT_KIT_EXPORT __declspec(dllimport)
#	endif

#	if defined(BUILD_QXT_MEDIA)
#   		define QXT_MEDIA_EXPORT __declspec(dllexport)
#	else
#   		define QXT_MEDIA_EXPORT __declspec(dllimport)
#	endif


#	if defined(BUILD_QXT_NETWORK)
#   		define QXT_NETWORK_EXPORT __declspec(dllexport)
#	else
#   		define QXT_NETWORK_EXPORT __declspec(dllimport)
#	endif


#	if defined(BUILD_QXT_SQL)
#   		define QXT_SQL_EXPORT __declspec(dllexport)
#	else
#   		define QXT_SQL_EXPORT __declspec(dllimport)
#	endif

#else

#    define QXT_CORE_EXPORT
#    define QXT_KIT_EXPORT
#    define QXT_GUI_EXPORT
#    define QXT_MEDIA_EXPORT
#    define QXT_NETWORK_EXPORT
#    define QXT_SQL_EXPORT




#endif










#if defined BUILD_QXT_GUI || defined BUILD_QXT_MEDIA  || defined  BUILD_QXT_SQL || defined BUILD_QXT_NETWORK || defined BUILD_QXT_KIT
#define BUILD_QXT_QT
#endif

#if defined BUILD_QXT_CORE ||  defined BUILD_QXT_GUI || defined BUILD_QXT_MEDIA  || defined  BUILD_QXT_SQL || defined BUILD_QXT_NETWORK || defined BUILD_QXT_KIT
#define BUILD_QXT
#endif











#endif //guards

