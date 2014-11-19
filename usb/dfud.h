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
    virtual QString what() const throw()  {return QObject::tr("Generic DFU error");}
};

class ErrorDfuTarget: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: File is not targeted for use by this device");}
};

class ErrorDfuFile: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: File is for this device but fails some vendor-specific verification test");}
};

class ErrorDfuWrite: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Device is unable to write memory");}
};

class ErrorDfuErase: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Memory erase function failed");}
};

class ErrorDfuCheckErased: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Memory erase check failed");}
};

class ErrorDfuProg: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Program memory function failed");}
};

class ErrorDfuVerify: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Programmed memory failed verification");}
};

class ErrorDfuAddress: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Cannot program memory due to received address that is out of range");}
};

class ErrorDfuNotDone: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Received DFU_DNLOAD with wLength = 0, but device does not think it has all of the data yet");}
};

class ErrorDfuFirmware: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Device’s firmware is corrupt. It cannot return to run-time (non-DFU) operations");}
};

class ErrorDfuVendor: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: iString indicates a vendor-specific error");}
};

class ErrorDfuUsbReset: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Device detected unexpected USB reset signaling");}
};

class ErrorDfuPor: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Device detected unexpected power on reset");}
};

class ErrorDfuUnknown: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Something went wrong, but the device does not know what it was");}
};

class ErrorDfuStalled: public ErrorDfu
{
    virtual QString what() const throw()  {return QObject::tr("DFU: Device stalled an unexpected request");}
};


class USBD;

class DFUD : public QObject
{
    Q_OBJECT
private:
    USBD* usbd;
    int dlnum;
protected:
    int getStatus();
    void dnLoad(const QByteArray& buf);
public:
    explicit DFUD(QObject *parent = 0);
    ~DFUD();

    bool open(int vid, int pid);
    void close();
    bool isActive();

    int test();
    void write(const QByteArray& buf);

signals:

public slots:

};

#endif // DFUD_H
