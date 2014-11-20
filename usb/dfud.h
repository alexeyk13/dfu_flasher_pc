/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef DFUD_H
#define DFUD_H

#include <QObject>
#include "../error.h"

class ErrorDfu: public Exception
{
public:
    ErrorDfu() throw() :Exception() {str = (QObject::tr("Generic DFU error"));}
};

class ErrorDfuTarget: public ErrorDfu
{
public:
    ErrorDfuTarget() throw() :ErrorDfu() {str = (QObject::tr("DFU: File is not targeted for use by this device"));}
};

class ErrorDfuFile: public ErrorDfu
{
public:
    ErrorDfuFile() throw() :ErrorDfu() {str = (QObject::tr("DFU: File is for this device but fails some vendor-specific verification test"));}
};

class ErrorDfuWrite: public ErrorDfu
{
public:
    ErrorDfuWrite() throw() :ErrorDfu() {str = (QObject::tr("DFU: Device is unable to write memory"));}
};

class ErrorDfuErase: public ErrorDfu
{
public:
    ErrorDfuErase() throw() :ErrorDfu() {str = (QObject::tr("DFU: Memory erase function failed"));}
};

class ErrorDfuCheckErased: public ErrorDfu
{
public:
    ErrorDfuCheckErased() throw() :ErrorDfu() {str = (QObject::tr("DFU: Memory erase check failed"));}
};

class ErrorDfuProg: public ErrorDfu
{
public:
    ErrorDfuProg() throw() :ErrorDfu() {str = (QObject::tr("DFU: Program memory function failed"));}
};

class ErrorDfuVerify: public ErrorDfu
{
public:
    ErrorDfuVerify() throw() :ErrorDfu() {str = (QObject::tr("DFU: Programmed memory failed verification"));}
};

class ErrorDfuAddress: public ErrorDfu
{
public:
    ErrorDfuAddress() throw() :ErrorDfu() {str = (QObject::tr("DFU: Cannot program memory due to received address that is out of range"));}
};

class ErrorDfuNotDone: public ErrorDfu
{
public:
    ErrorDfuNotDone() throw() :ErrorDfu() {str = (QObject::tr("DFU: Received DFU_DNLOAD with wLength = 0, but device does not think it has all of the data yet"));}
};

class ErrorDfuFirmware: public ErrorDfu
{
public:
    ErrorDfuFirmware() throw() :ErrorDfu() {str = (QObject::tr("DFU: Device’s firmware is corrupt. It cannot return to run-time (non-DFU) operations"));}
};

class ErrorDfuVendor: public ErrorDfu
{
public:
    ErrorDfuVendor() throw() :ErrorDfu() {str = (QObject::tr("DFU: iString indicates a vendor-specific error"));}
};

class ErrorDfuUsbReset: public ErrorDfu
{
public:
    ErrorDfuUsbReset() throw() :ErrorDfu() {str = (QObject::tr("DFU: Device detected unexpected USB reset signaling"));}
};

class ErrorDfuPor: public ErrorDfu
{
public:
    ErrorDfuPor() throw() :ErrorDfu() {str = (QObject::tr("DFU: Device detected unexpected power on reset"));}
};

class ErrorDfuUnknown: public ErrorDfu
{
public:
    ErrorDfuUnknown() throw() :ErrorDfu() {str = (QObject::tr("DFU: Something went wrong, but the device does not know what it was"));}
};

class ErrorDfuStalled: public ErrorDfu
{
public:
    ErrorDfuStalled() throw() :ErrorDfu() {str = (QObject::tr("DFU: Device stalled an unexpected request"));}
};


class USBD;

class DFUD : public QObject
{
    Q_OBJECT
private:
    USBD* usbd;
    int dlnum, ulnum;
protected:
    int getState();
    int getStatus();
    void clrStatus();
    void dnLoad(const QByteArray& buf);
    QByteArray upLoad();
public:
    explicit DFUD(QObject *parent = 0);
    ~DFUD();

    bool open(int vid, int pid);
    void close();
    bool isActive();

    void write(const QByteArray& buf);
    QByteArray read();

signals:

public slots:

};

#endif // DFUD_H
