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
	special module for Audio and Video Stuff
*/


/**

\page building

\section start Getting Started 
At first you need qmake. You get it from the qt toolkit by TrollTech

\subsection get Get the sources
you can either use a release package from the download section or get it from svn
	\code
	svn co https://libqxt.svn.sourceforge.net/svnroot/libqxt libqxt
	\endcode

\section conf  Configuration
in the projects root there is a file called config.pri, open it and you will see the different options you may configure

\section instdir Installation Path
set QXTINSTALLDIR to where you want to install libqxt. for unix the librarys will also be installed in /usr/lib, the docs in /usr/doc and the includes in /usr/include
if you want another prefix then /usr define QXTUNIXPREFIX

\subsection modules Modules
the variable QXT contains all the modules you want similar to the QT variable of qt.  
eg if you don't want the sql module type QXT-=sql or if you want just the core type QXT=core

\subsection deps Depencys
libqxt depends on several third party libs. if you don't want that you may use the QXT_LIBS variable to  tell the buildsystem to exlcude these librarys.
\note if you exclude librarys the features depending on the libraray will not be available

\subsection stability Stability
you may configure the desired state of stability by the variable QXT_stability. Developers mark their packages to be stable or broken on specific platforms.
\note if you have custom mkspecs this will not work properly. check the next section for a workaround

\subsection ignore  Ignore Stability
undependend from the above declaration you may set  QXT_ignore_stability to compile a package regardless what its stability is set.  This couses aditional abi incompatibility and should only used if realy necesary. If a package has not yet been set to stable but you find it works very well, please make a bug report.



\section make  Making
make sure your qt environment is propably setup.

type 
\code
qmake && make
\endcode
and fetch some coffee
 
\section install  Installing
type as root

\code
make install
\endcode

\note this will also install qxt.prf to your qtdir/mkspecs/features   if you ever change your qt you need to copy that file

\section useage  Using Qxt in your project

add 
\code
CONFIG	+= qxt
QXT	+= core media
\endcode
to your project file.
the QXT variable defines the modules you want. In this case core and media are used
\note modules may depend on other modules. these are automaticly added.


*/
/*! \mainpage Qt extended Librarys
 *
 *
 * Qxt Provides Classes for extended needs based on the Qt Library by Trolltech
 *
 * Checkout the classes list

\image html qxbig.jpg
 * 
 */


#include <QxtPairList.h>
#include <QxtNullable.h>
