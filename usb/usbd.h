/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef USBD_H
#define USBD_H

#include "../error.h"
#include <stdint.h>
#include "usb.h"
#include <QSet>
#include "config.h"
#include <QObject>

class ErrorUsb: public Exception
{
    virtual QString what() const throw()  {return QObject::tr("Generic USB error");}
};

class ErrorLibUsb: public ErrorUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb error");}
};

class ErrorLibUsbIO: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - IO error");}
};

class ErrorLibUsbInvalidParam: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Invalid parameter");}
};

class ErrorLibUsbAccessDenied: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Access denied");}
};

class ErrorLibUsbNoDevice: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - No device");}
};

class ErrorLibUsbNotFound: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Entity not found");}
};

class ErrorLibUsbBusy: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Busy");}
};

class ErrorLibUsbTimeout: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Timeout");}
};

class ErrorLibUsbOverflow: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Overflow");}
};

class ErrorLibUsbPipe: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Pipe error");}
};

class ErrorLibUsbInterrupted: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - System call interrupted");}
};

class ErrorLibUsbOutOfMemory: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Out of memory");}
};

class ErrorLibUsbNotSupported: public ErrorLibUsb
{
    virtual QString what() const throw()  {return QObject::tr("Libusb - Operation not supported");}
};


class QByteArray;

class USBD
{
private:
    static struct libusb_context* ctx;
    static int instanceCount;
	static QSet<struct libusb_device*> devs;

	struct libusb_device_handle* handle;
protected:
	void checkStatus(int res);
	struct libusb_device* getFirstFree(int vid, int pid);
public:
    USBD();
    ~USBD();

	static bool isAvailable(int vid, int pid);
    bool open(int vid, int pid);
	void close();
    bool isActive() {return handle != NULL;}

	void controlReq(const SETUP& setup, QByteArray& data, int timeout = PORT_DEFAULT_TIMEOUT);
	void bulkWrite(const QByteArray& data, int ep, int timeout = PORT_DEFAULT_TIMEOUT);
	QByteArray bulkRead(int ep, int maxSize, int timeout = PORT_DEFAULT_TIMEOUT);
};

#endif // USBD_H
