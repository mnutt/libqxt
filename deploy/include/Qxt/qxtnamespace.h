/*******************************************************************
Qt extended Library
Copyright (C) 2007 libqxt
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTNAMSPACE_GUARD_H
#define QXTNAMSPACE_GUARD_H

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
                NoError,				/*!< everything fine  */
                UnknownError,				/*!< a not defined error */
                LogicalError,				/*!< something happened that makes no sense (e.g. you tryed to compare apples and bananas) */
		Bug,					/*!< that should not happen. please report any ocurence of it. */
		UnexpectedEndOfFunction,		/*!< suddenly the function returned where it should not. please report this behaiviour */
		NotImplemented,           		/*!< the feature you requested has not been implemented for this situation. this could also mean you are trying to compare apples and bananas. */
                CodecError,				/*!< Something went wrong with some codec. Please check if your codec is supported */
                NotInitialised,				/*!< Somone tryed to call a function of an object that needs to be start() ed  or something like it. */
		EndOfFile,				/*!< The end of the Input has been reached. There is no more data. */
                FileIOError,				/*!< File Input/Output Error*/
                FormatError,				/*!< The Format of the input is corupted or not supported. */   //10
                DeviceError,				/*!< The Device of the Computer reported failure or we are not able to comunicate with it.*/
                SDLError,				/*!< SDL reported an error */
		InsufficientMemory,			/*!< Not enough memory to perform the action. */
		SeeErrorString				/*!< The Error has no definition here, but the Error String should tell you more. This is mostly used for third party errors. */
                };

};

#endif

