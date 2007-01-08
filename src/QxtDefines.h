#ifndef QXTDEFINES_H
#define QXTDEFINES_H

#if !defined(Q_OS_WIN32)
#   define QXT_DLLEXPORT
#elif defined(BUILDING_QXT_LIBRARY)
#   define QXT_DLLEXPORT __declspec(dllexport)
#else
#   define QXT_DLLEXPORT __declspec(dllimport)
#endif

#endif
