/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/


/** \defgroup core Core
        The Core contains naturaly  the most important parts of Qxt everything is based one. it has no QT depencies and is licenced under pure lgpl
*/

/** \defgroup kit Kit
        the kit module contains the base parts of Qxt that depend on QtCore
*/

/** \defgroup sql Sql
        parts that depend on QtSql (and at least QtCore)
*/

/** \defgroup network  Network
        parts that depend on QtNetwork (and at least QtCore)
*/

/** \defgroup gui Gui
        parts that depend on QtGui (and at least QtCore)
*/

/** \defgroup media Media
        special module for Media Classes
*/

/** \defgroup curses  Curses
        Qt like ncurses Frontend
*/

/** \defgroup web  Web
        Qt like Web Developement tools
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





#define QXT_VERSION (  (2<<16) + (2<<8) + 3 ) 



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

#	if defined(BUILD_QXT_GUI) || defined(QDESIGNER_EXPORT_WIDGETS)
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

#	if defined(BUILD_QXT_WEB)
#   		define QXT_WEB_EXPORT __declspec(dllexport)
#	else
#   		define QXT_WEB_EXPORT __declspec(dllimport)
#	endif


#else

#    define QXT_CORE_EXPORT
#    define QXT_KIT_EXPORT
#    define QXT_GUI_EXPORT
#    define QXT_MEDIA_EXPORT
#    define QXT_NETWORK_EXPORT
#    define QXT_SQL_EXPORT
#    define QXT_WEB_EXPORT




#endif










#if defined BUILD_QXT_GUI || defined BUILD_QXT_MEDIA  || defined  BUILD_QXT_SQL || defined BUILD_QXT_NETWORK || defined BUILD_QXT_KIT || defined BUILD_QXT_WEB
#define BUILD_QXT_QT
#endif

#if defined BUILD_QXT_CORE ||  defined BUILD_QXT_GUI || defined BUILD_QXT_MEDIA  || defined  BUILD_QXT_SQL || defined BUILD_QXT_NETWORK || defined BUILD_QXT_KIT || defined BUILD_QXT_WEB
#define BUILD_QXT
#endif











#endif //guards

