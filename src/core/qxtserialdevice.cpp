#include "qxtserialdevice.h"
#include "qxtserialdevice_p.h"

QxtSerialDevicePrivate::QxtSerialDevicePrivate() {
    fd = -1;
    notifier = 0;
}

/**
 * Creates a new QxtSerialDevice with the specified parent and sets the device name to \a device.
 */
QxtSerialDevice::QxtSerialDevice(const QString& device, QObject* parent) : QIODevice(parent) {
    QXT_INIT_PRIVATE(QxtSerialDevice);
    setDeviceName(device);
    setBaud(Baud9600);
}

/**
 * Creates a new QxtSerialDevice with the specified parent.
 */
QxtSerialDevice::QxtSerialDevice(QObject* parent) : QIODevice(parent) {
    QXT_INIT_PRIVATE(QxtSerialDevice);
    setBaud(Baud9600);
}

/**
 * \reimp
 */
bool QxtSerialDevice::atEnd() const {
    return (bytesAvailable() == 0);
}

/**
 * \reimp
 */
bool QxtSerialDevice::canReadLine() const {
    if(QIODevice::canReadLine()) return true;
    if(openMode() & QIODevice::Unbuffered) return false;
    if(qxt_d().constFillBuffer()) return false;
    return qxt_d().buffer.contains('\n');
}

/**
 * \reimp
 */
bool QxtSerialDevice::isSequential() const {
    return true;
}

/**
 * Sets the device name to \a device. This is a device node like "/dev/ttyS0" on UNIX or a device name like "COM1" on Windows.
 * \sa deviceName
 */
void QxtSerialDevice::setDeviceName(const QString& device) {
    qxt_d().device = device;
}

/**
 * Returns the current device name.
 * \sa device
 */
QString QxtSerialDevice::deviceName() const {
    return qxt_d().device;
}

/**
 * Returns the file descriptor for the open device. If the device is not open, this function returns -1.
 */
int QxtSerialDevice::handle() const {
    if(!isOpen()) return -1;
    return qxt_d().fd;
}

bool QxtSerialDevice::open(const QString& device, OpenMode mode) {
    setDeviceName(device);
    return(open(mode));
}

bool QxtSerialDevice::setPortSettings(PortSettings setup) {
    qxt_d().portSettings = setup;
    return qxt_d().setPortSettings(setup);
}

QxtSerialDevice::PortSettings QxtSerialDevice::portSettings() const {
    return qxt_d().portSettings;
}

QxtSerialDevice::PortSetting QxtSerialDevice::dataBits() const {
    return PortSetting(int(qxt_d().portSettings & BitMask));
}

QxtSerialDevice::PortSetting QxtSerialDevice::flowControl() const {
    return PortSetting(int(qxt_d().portSettings & FlowMask));
}

QxtSerialDevice::PortSetting QxtSerialDevice::parity() const {
    return PortSetting(int(qxt_d().portSettings & ParityMask));
}

QxtSerialDevice::PortSetting QxtSerialDevice::stopBits() const {
    return PortSetting(int(qxt_d().portSettings & StopMask));
}

