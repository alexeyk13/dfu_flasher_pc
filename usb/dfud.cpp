/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "dfud.h"
#include "usbd.h"
#include "dfu.h"

DFUD::DFUD(QObject *parent) :
    QObject(parent)
{
    usbd = new USBD();
}

DFUD::~DFUD()
{
    delete usbd;
}

int DFUD::getState()
{
    SETUP setup;
    setup.bmRequestType = BM_REQUEST_DIRECTION_DEVICE_TO_HOST | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
    setup.bRequest = DFU_GETSTATE;
    setup.wValue = 0;
    setup.wIndex = 0;
    setup.wLength = 1;
    QByteArray data;
    usbd->controlReq(setup, data);
    if (data.size() != 1)
        throw ErrorDfu();

    return data[0];
}

int DFUD::getStatus()
{
    SETUP setup;
    setup.bmRequestType = BM_REQUEST_DIRECTION_DEVICE_TO_HOST | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
    setup.bRequest = DFU_GETSTATUS;
    setup.wValue = 0;
    setup.wIndex = 0;
    setup.wLength = 6;
    QByteArray data;
    usbd->controlReq(setup, data);
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

void DFUD::dnLoad(const QByteArray& buf)
{
    SETUP setup;
    setup.bmRequestType = BM_REQUEST_DIRECTION_HOST_TO_DEVICE | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
    setup.bRequest = DFU_DNLOAD;
    setup.wValue = dlnum++;
    setup.wIndex = 0;
    setup.wLength = buf.size();
    QByteArray localBuf(buf);
    usbd->controlReq(setup, localBuf);
}

QByteArray DFUD::upLoad()
{
    SETUP setup;
    setup.bmRequestType = BM_REQUEST_DIRECTION_DEVICE_TO_HOST | BM_REQUEST_TYPE_CLASS | BM_REQUEST_RECIPIENT_INTERFACE;
    setup.bRequest = DFU_UPLOAD;
    setup.wValue = ulnum++;
    setup.wIndex = 0;
    setup.wLength = DFU_BLOCK_SIZE + 64 + 1;
    QByteArray buf;
    usbd->controlReq(setup, buf);
    return buf;
}

bool DFUD::open(int vid, int pid)
{
    if (!usbd->isActive())
        dlnum = ulnum = 0;
    if (!usbd->open(vid, pid))
        return false;
    //TODO: clr state
    return true;
}

void DFUD::close()
{
    usbd->close();
}

bool DFUD::isActive()
{
    return usbd->isActive();
}

int DFUD::test()
{
    return getStatus();
}

void DFUD::write(const QByteArray &buf)
{
    //transfer
    dnLoad(buf);
    while (getStatus() == DFU_STATE_DNBUSY) {}
    //transfer complete
    dnLoad(QByteArray());
    getStatus();
}

QByteArray DFUD::read()
{
    return upLoad();
}
