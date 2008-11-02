#ifndef QXTSERIALDEVICE_H
#define QXTSERIALDEVICE_H

#include "qxtglobal.h"
#include "qxtpimpl.h"
#include <QIODevice>

class QxtSerialDevicePrivate;
class QXT_CORE_EXPORT QxtSerialDevice : public QIODevice {
Q_OBJECT
public:
    enum BaudRate {
        Baud110, Baud300, Baud600, Baud1200, Baud2400, Baud4800, Baud9600, Baud19200, Baud38400, Baud57600, Baud115200
    };

    enum PortSetting {
        Bit8 = 0,
        Bit7 = 1,
        Bit6 = 2,
        Bit5 = 3,
        BitMask = 3,
        FlowOff = 0,
        FlowRtsCts = 4,
        FlowXonXoff = 8,
        FlowMask = 12,
        ParityNone = 0,
        ParityOdd = 16,
        ParityEven = 32,
        ParityMark = 48,
        ParitySpace = 64,
        ParityMask = 112,
        Stop1 = 0,
        Stop2 = 128,
        StopMask = 128
    };
    Q_DECLARE_FLAGS(PortSettings, PortSetting);

    QxtSerialDevice(const QString& device, QObject* parent = 0);
    QxtSerialDevice(QObject* parent = 0);

    virtual bool atEnd() const;
    virtual qint64 bytesAvailable() const;
    virtual bool canReadLine() const;
    virtual void close();
    virtual bool isSequential() const;
    bool open(const QString& device, OpenMode mode);
    virtual bool open(OpenMode mode);
    int handle() const;

    void setDeviceName(const QString& device);
    QString deviceName() const;

    bool setBaud(BaudRate rate);
    BaudRate baud() const;

    bool setPortSettings(PortSettings setup);
    PortSettings portSettings() const;
    PortSetting dataBits() const;
    PortSetting flowControl() const;
    PortSetting parity() const;
    PortSetting stopBits() const;

protected:
    virtual qint64 readData(char* data, qint64 maxSize);
    virtual qint64 writeData(const char* data, qint64 maxSize);

private:
    QXT_DECLARE_PRIVATE(QxtSerialDevice);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QxtSerialDevice::PortSettings);

#endif
