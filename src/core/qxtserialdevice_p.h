#ifndef QXTSERIALDEVICE_P_H
#define QXTSERIALDEVICE_P_H

#include "qxtserialdevice.h"
#include <QByteArray>

#ifdef Q_OS_UNIX
#include <termios.h>
#endif

class QSocketNotifier;

class QxtSerialDevicePrivate : public QObject, public QxtPrivate<QxtSerialDevice> {
Q_OBJECT
public:
    QxtSerialDevicePrivate();
    
    int fd;
    bool errorState;
    QSocketNotifier* notifier;
    mutable QByteArray buffer;
    QString device;
    int baud, flow, format;
    QxtSerialDevice::PortSettings portSettings; // duplicated for convenience
#ifdef Q_OS_UNIX
    termios reset, settings;
#endif

    qint64 deviceBuffer() const;
    bool setPortSettings(QxtSerialDevice::PortSettings settings);
    bool updateSettings();
    
public slots:
    int fillBuffer();
    int constFillBuffer() const;
};

#endif // QXTSERIALDEVICE_P_H
