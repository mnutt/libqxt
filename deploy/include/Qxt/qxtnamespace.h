/*******************************************************************
Qt extended Library
Copyright (C) 2007 libqxt
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTGUI_H
#define QXTGUI_H

#include <Qxt/qxtglobal.h>


/**
    \namespace Qxt
    \ingroup core
    \brief The Qxt Namespace

    The Qxt Namespace

*/


#if defined BUILD_QXT_QT 
#include <QObject>

class QXT_KIT_EXPORT Qxt  : public QObject
{
	Q_OBJECT
	Q_ENUMS(Rotation)
	Q_ENUMS(DecorationStyle)
	Q_ENUMS(QxtAVFileFlags)
	Q_ENUMS(ErrorCode)


public:
#else
namespace Qxt {
#endif




	/*!
	\enum Qxt::Rotation
	This enum describes the rotation.
	*/
	enum Rotation
	{
		NoRotation		= 0,		/*!< No rotation. */
		UpsideDown		= 180,		/*!< Upside down (180 degrees). */
		Clockwise		= 90,		/*!< Clockwise (90 degrees). */
		CounterClockwise	= 270		/*!< CounterClockwise (-90 degrees).  */
	};
	
	/*!
	\enum Qxt::DecorationStyle

	This enum describes the decoration style.
	*/

	enum DecorationStyle
	{
		NoDecoration,				/*!< No decoration */
		Buttonlike,				/*!< A style like in Qt Designer's Widget Box. */
		Menulike				/*!< A menu alike style. */
	};


        enum QxtAVFileFlags
                {
                preload,
                fullLoad
                };

	/*!
	\enum Qxt::ErrorCode
	The error Code dropped by QxtError
	*/
        enum ErrorCode
                {
                NoError,				/*!<  */
                UnknownError,				/*!<  */
                LogicalError,				/*!<  */
		Bug,					/*!<  */
		UnexpectedEndOfFunction,		/*!<  */
		NotImplemented,           		/*!<  */
                CodecError,				/*!<  */
                NotInitialised,				/*!<  */
		EndOfFile,				/*!<  */
                FileIOError,				/*!<  */
                FormatError,				/*!<  */   //10
                DeviceError,				/*!<  */
                SDLError,				/*!<  */
		InsufficientMemory,			/*!<  */
		SeeErrorString				/*!<  */
                };

};

#endif // QXTGUI_H

