/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "usbd.h"

#if defined(_WIN32)
#include "libusb.h"
#else
#include <libusb-1.0/libusb.h>
#endif

struct libusb_context* USBD::ctx = NULL;
int USBD::instanceCount = 0;
QSet<struct libusb_device*> USBD::devs;

USBD::USBD() :
	handle(NULL)
{
	if (instanceCount++ == 0)
        checkStatus(libusb_init(&ctx));
}

USBD::~USBD()
{
	close();
    if (ctx && --instanceCount == 0)
        libusb_exit(ctx);
}

void USBD::checkStatus(int res)
{
	switch (res)
	{
	case LIBUSB_SUCCESS:
		break;
	case LIBUSB_ERROR_IO:
		throw ErrorLibUsbIO();
		break;
	case LIBUSB_ERROR_INVALID_PARAM:
		throw ErrorLibUsbInvalidParam();
		break;
	case LIBUSB_ERROR_ACCESS:
		throw ErrorLibUsbAccessDenied();
		break;
	case LIBUSB_ERROR_NO_DEVICE:
		throw ErrorLibUsbNoDevice();
		break;
	case LIBUSB_ERROR_NOT_FOUND:
		throw ErrorLibUsbNotFound();
		break;
	case LIBUSB_ERROR_BUSY:
		throw ErrorLibUsbBusy();
		break;
	case LIBUSB_ERROR_TIMEOUT:
		throw ErrorLibUsbTimeout();
		break;
	case LIBUSB_ERROR_OVERFLOW:
		throw ErrorLibUsbOverflow();
		break;
	case LIBUSB_ERROR_PIPE:
		throw ErrorLibUsbPipe();
		break;
	case LIBUSB_ERROR_INTERRUPTED:
		throw ErrorLibUsbInterrupted();
		break;
	case LIBUSB_ERROR_NO_MEM:
		throw ErrorLibUsbOutOfMemory();
		break;
	case LIBUSB_ERROR_NOT_SUPPORTED:
		throw ErrorLibUsbNotSupported();
		break;
	default:
		if (res < 0)
			throw ErrorLibUsb();
	}
}

struct libusb_device* USBD::getFirstFree(int vid, int pid)
{
	libusb_device* dev = NULL;
	libusb_device **list;
	struct libusb_device_descriptor desc;

	ssize_t cnt = libusb_get_device_list(ctx, &list);
	try
	{
		for (ssize_t i = 0; i < cnt; ++i)
		{
			checkStatus(libusb_get_device_descriptor(list[i], &desc));
			if (desc.idVendor == vid && desc.idProduct == pid && !devs.contains(list[i]))
			{
				dev = list[i];
				devs.insert(dev);
				libusb_ref_device(dev);
				break;
			}
		}
		libusb_free_device_list(list, true);
	}
	catch (...)
	{
		libusb_free_device_list(list, true);
		throw;
	}
	return dev;
}

bool USBD::isAvailable(int vid, int pid)
{
	bool res = false;
    USBD usbd;
    struct libusb_device* dev = usbd.getFirstFree(vid, pid);
	if (dev)
	{
		devs.remove(dev);
		libusb_unref_device(dev);
		res = true;
	}
	return res;
}

bool USBD::open(int vid, int pid)
{
	if (handle == NULL)
	{
		libusb_device* dev = getFirstFree(vid, pid);
		if (dev)
		{
			checkStatus(libusb_open(dev, &handle));
			libusb_unref_device(dev);
		}
	}
	return handle != NULL;
}

void USBD::close()
{
	if (handle)
	{
		devs.remove(libusb_get_device(handle));
		libusb_close(handle);
		handle = NULL;
	}
}

void USBD::controlReq(const SETUP &setup, QByteArray &data, int timeout)
{
	if (handle == NULL)
		throw ErrorLibUsbNoDevice();
	if (setup.bmRequestType & BM_REQUEST_DIRECTION_DEVICE_TO_HOST)
		data.resize(setup.wLength);
	int res = libusb_control_transfer(handle, setup.bmRequestType, setup.bRequest, setup.wValue, setup.wIndex, reinterpret_cast<unsigned char*>(data.data()), setup.wLength, timeout);
	checkStatus(res);
	if (setup.bmRequestType & BM_REQUEST_DIRECTION_DEVICE_TO_HOST)
		data.resize(res);
}

void USBD::bulkWrite(const QByteArray &data, int ep, int timeout)
{
	if (handle == NULL)
		throw ErrorLibUsbNoDevice();
	int transferred;
	checkStatus(libusb_bulk_transfer(handle, ep, reinterpret_cast<unsigned char*>(QByteArray(data).data()), data.size(), &transferred, timeout));
	if (transferred != data.size())
		throw ErrorLibUsbIO();
}

QByteArray USBD::bulkRead(int ep, int maxSize, int timeout)
{
	if (handle == NULL)
		throw ErrorLibUsbNoDevice();
	QByteArray res(maxSize, 0x0);
	int transferred;
	checkStatus(libusb_bulk_transfer(handle, ep | BM_REQUEST_DIRECTION_DEVICE_TO_HOST, reinterpret_cast<unsigned char*>(res.data()), maxSize, &transferred, timeout));
	if (!transferred)
        throw ErrorLibUsbTimeout();
	return res.left(transferred);
}
