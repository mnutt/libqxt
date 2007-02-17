/*******************************************************************
Qt extended Library
Copyright (C) 2007 libqxt
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTGUI_H
#define QXTGUI_H

#include <QObject>
#include <Qxt/qxtglobal.h>

/*!
    \enum QxtGui::Rotation

    This enum describes the rotation.

    \value NoRotation        No rotation.
    \value UpsideDown        Upside down (180 degrees).
    \value Clockwise         Clockwise (90 degrees).
    \value CounterClockwise  CounterClockwise (-90 degrees).
 */

/*!
    \enum QxtGui::DecorationStyle

    This enum describes the decoration style.

    \value NoDecoration    No decoration
    \value Buttonlike      A style like in Qt Designer's Widget Box.
    \value Menulike        A menu alike style.
 */


#if defined BUILD_QXT

class QXT_KIT_EXPORT Qxt  : public QObject
{
	Q_OBJECT
	Q_ENUMS(Rotation)
	Q_ENUMS(DecorationStyle)
	Q_ENUMS(QxtAVFileFlags)

public:
#else
namespace Qxt {
#endif


	enum Rotation
	{
		NoRotation		= 0,
		UpsideDown		= 180,
		Clockwise		= 90,
		CounterClockwise	= 270
	};
	
	enum DecorationStyle
	{
		NoDecoration,
		Buttonlike,
		Menulike
	};


        enum QxtAVFileFlags
                {
                preload,
                fullLoad
                };


        enum ErrorCode
                {
                NoError
                FileInputError
                FormatError
                CodecError
                };

};

#endif // QXTGUI_H

