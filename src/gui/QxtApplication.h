/*******************************************************************
Qt extended Library 
Copyright (C) 2007 J-P Nurmi <jpnurmi@gmail.com>
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTAPPLICATION_H
#define QXTAPPLICATION_H

#include <QPair>
#include <QList>
#include <QMultiHash>
#include <QApplication>
#include <Qxt/qxtglobal.h>

typedef QPair<uint, uint> Identifier;
typedef QList<Identifier> Identifiers;
typedef QPair<QWidget*, const char*> Receiver;
typedef QList<Receiver> Receivers;

class QXT_GUI_EXPORT QxtApplication : public QApplication
{
public:
	QxtApplication(int& argc, char** argv);
	QxtApplication(int& argc, char** argv, bool GUIenabled);
	QxtApplication(int& argc, char** argv, Type type);
#if defined(Q_WS_X11)
	QxtApplication(Display* display, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0);
	QxtApplication(Display* display, int& argc, char** argv, Qt::HANDLE visual = 0, Qt::HANDLE colormap = 0);
#endif
	virtual ~QxtApplication();
		
#if defined(Q_WS_X11)
	virtual bool x11EventFilter(XEvent* event);
#elif defined(Q_WS_WIN)
	virtual bool winEventFilter(MSG* msg, long* result);
#endif

	bool addHotKey(Qt::KeyboardModifiers modifiers, Qt::Key key, QWidget* receiver, const char* member);
	bool removeHotKey(Qt::KeyboardModifiers modifiers, Qt::Key key, QWidget* receiver, const char* member);

protected:
	virtual uint nativeKeycode(Qt::Key key) const;
	virtual uint nativeModifiers(Qt::KeyboardModifiers modifiers) const;
	
private:
	bool registerHotKey(uint modifiers, uint keycode, QWidget* receiver);
	bool unregisterHotKey(uint modifiers, uint keycode, QWidget* receiver);
	void activateHotKey(uint modifiers, uint keycode) const;

	QMultiHash<Identifier, Receiver> hotkeys;
};

inline uint qHash(const QPair<uint, uint>& value)
{
	return qHash(value.first) ^ qHash(value.second);
}

#endif // QXTAPPLICATION_H
