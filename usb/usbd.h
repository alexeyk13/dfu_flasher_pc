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
public:
    ErrorUsb() throw() :Exception() {str = (QObject::tr("Generic USB error"));}
};

class ErrorLibUsb: public ErrorUsb
{
public:
    ErrorLibUsb() throw() :ErrorUsb() {str = (QObject::tr("Libusb error"));}
};

class ErrorLibUsbIO: public ErrorLibUsb
{
public:
    ErrorLibUsbIO() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - IO error"));}
};

class ErrorLibUsbInvalidParam: public ErrorLibUsb
{
public:
    ErrorLibUsbInvalidParam() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Invalid parameter"));}
};

class ErrorLibUsbAccessDenied: public ErrorLibUsb
{
public:
    ErrorLibUsbAccessDenied() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Access denied"));}
};

class ErrorLibUsbNoDevice: public ErrorLibUsb
{
public:
    ErrorLibUsbNoDevice() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - No device"));}
};

class ErrorLibUsbNotFound: public ErrorLibUsb
{
public:
    ErrorLibUsbNotFound() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Entity not found"));}
};

class ErrorLibUsbBusy: public ErrorLibUsb
{
public:
    ErrorLibUsbBusy() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Busy"));}
};

class ErrorLibUsbTimeout: public ErrorLibUsb
{
public:
    ErrorLibUsbTimeout() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Timeout"));}
};

class ErrorLibUsbOverflow: public ErrorLibUsb
{
public:
    ErrorLibUsbOverflow() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Overflow"));}
};

class ErrorLibUsbPipe: public ErrorLibUsb
{
public:
    ErrorLibUsbPipe() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Pipe error"));}
};

class ErrorLibUsbInterrupted: public ErrorLibUsb
{
public:
    ErrorLibUsbInterrupted() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - System call interrupted"));}
};

class ErrorLibUsbOutOfMemory: public ErrorLibUsb
{
public:
    ErrorLibUsbOutOfMemory() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Out of memory"));}
};

class ErrorLibUsbNotSupported: public ErrorLibUsb
{
public:
    ErrorLibUsbNotSupported() throw() :ErrorLibUsb() {str = (QObject::tr("Libusb - Operation not supported"));}
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
