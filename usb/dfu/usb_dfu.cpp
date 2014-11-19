/*
    RadCOMM - CDC communication module for Quarta RAD
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "usb_dfu.h"
#include "../usb.h"
//#include "../../../delay.h"
#include "usb_dfu_defs.h"
#include "usb_dfu_error.h"
/*
UsbDfu::UsbDfu(int vid, int pid, int ep, PhoneObject* parent) :
	Port(parent),
	vid(-1),
	pid(-1),
	ep(-1),
	usb(NULL),
	usbTimeout(1000)
{
	UsbDfu::vid = vid;
	UsbDfu::pid = pid;
	UsbDfu::ep = ep;
	usb = new Usb;
}

UsbDfu::~UsbDfu()
{
	delete usb;
}

int UsbDfu::getStatus()
{
	SETUP setup;
	setup.bmRequestType = BM_REQUEST_DIRECTION_DEVICE_TO_HOST | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
	setup.bRequest = DFU_GETSTATUS;
	setup.wValue = 0;
	setup.wIndex = 0;
	setup.wLength = 6;
	QByteArray data;
	usb->controlReq(setup, data);
	if (data.size() != 6)
		throw ErrorDfu();

	switch (data[0])
	{
	case DFU_STATUS_OK:
		break;
	case DFU_STATUS_TARGET:
		throw ErrorDfuTarget();
		break;
	case DFU_STATUS_FILE:
		throw ErrorDfuFile();
		break;
	case DFU_STATUS_WRITE:
		throw ErrorDfuWrite();
		break;
	case DFU_STATUS_ERASE:
		throw ErrorDfuErase();
		break;
	case DFU_STATUS_CHECK_ERASED:
		throw ErrorDfuCheckErased();
		break;
	case DFU_STATUS_PROG:
		throw ErrorDfuProg();
		break;
	case DFU_STATUS_VERIFY:
		throw ErrorDfuVerify();
		break;
	case DFU_STATUS_ADDRESS:
		throw ErrorDfuAddress();
		break;
	case DFU_STATUS_NOTDONE:
		throw ErrorDfuNotDone();
		break;
	case DFU_STATUS_FIRMWARE:
		throw ErrorDfuFirmware();
		break;
	case DFU_STATUS_VENDOR:
		throw ErrorDfuVendor();
		break;
	case DFU_STATUS_USBR:
		throw ErrorDfuUsbReset();
		break;
	case DFU_STATUS_POR:
		throw ErrorDfuPor();
		break;
	case DFU_STATUS_UNKNOWN:
		throw ErrorDfuUnknown();
		break;
	case DFU_STATUS_STALLEDPKT:
		throw ErrorDfuStalled();
		break;
	default:
		throw ErrorDfu();
	}
	return data[4];
}

int UsbDfu::getState()
{
	SETUP setup;
	setup.bmRequestType = BM_REQUEST_DIRECTION_DEVICE_TO_HOST | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
	setup.bRequest = DFU_GETSTATE;
	setup.wValue = 0;
	setup.wIndex = 0;
	setup.wLength = 1;
	QByteArray data;
	usb->controlReq(setup, data);
	if (data.size() != 1)
		throw ErrorDfu();

	return data[0];
}

void UsbDfu::dnLoad(const QByteArray &buf, int dlNum)
{
	SETUP setup;
	setup.bmRequestType = BM_REQUEST_DIRECTION_HOST_TO_DEVICE | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
	setup.bRequest = DFU_DNLOAD;
	setup.wValue = dlNum;
	setup.wIndex = 0;
	setup.wLength = buf.size();
	QByteArray localBuf(buf);
	usb->controlReq(setup, localBuf);
}

void UsbDfu::upLoad(QByteArray &buf, int ulNum, int timeout)
{
	SETUP setup;
	setup.bmRequestType = BM_REQUEST_DIRECTION_DEVICE_TO_HOST | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
	setup.bRequest = DFU_UPLOAD;
	setup.wValue = ulNum;
	setup.wIndex = 0;
	setup.wLength = 0x1000;
	usb->controlReq(setup, buf, timeout);
}

void UsbDfu::internalOpen()
{
	while (!usb->openIfPresent(vid, pid))
	{
		sync(true);
		sleep_ms(500);
	}
}

void UsbDfu::internalClose()
{
	usb->close();
}

void UsbDfu::internalWrite(const QByteArray &buf)
{
	if (ep)
	{
		dnLoad(UInt32Data(buf.size()), 0);
		usb->bulkWrite(buf, ep);
	}
	else
		dnLoad(buf, 0);
	int state = getStatus();
	while (state != DFU_STATE_DNLOAD_IDLE && state != DFU_STATE_ERROR)
	{
		sync();
		sleep_ms(usbTimeout);
		state = getStatus();
	}

	dnLoad(QByteArray(), 1);

	state = getStatus();
	while (state != DFU_STATE_IDLE && state != DFU_STATE_ERROR)
	{
		sync(true);
//		sleep_ms(usbTimeout);
		state = getStatus();
	}
}

void UsbDfu::internalRead(QByteArray &buf, int maxSize, int timeout)
{
	Q_UNUSED(maxSize);
	getStatus();
	upLoad(buf, 0, timeout);
	if (ep && static_cast<unsigned int>(buf.size()) >= sizeof(uint32_t))
	{
		int size = UInt32At(buf);
		if (size)
			buf = usb->bulkRead(ep, size);
	}
}
*/
