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

bool DFUD::open(int vid, int pid)
{
    if (!usbd->open(vid, pid))
        return false;
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
