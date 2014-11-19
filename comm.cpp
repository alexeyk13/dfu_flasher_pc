/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "comm.h"
#include "usb/usbd.h"
#include "config.h"
#include "error.h"

Comm::Comm(QObject *parent) :
    QObject(parent)
{
    usbd = new USBD();
}

Comm::~Comm()
{
    delete usbd;
}

bool Comm::isActive()
{
    return usbd->isActive();
}

bool Comm::open()
{
    if (usbd->isActive())
        return true;
    if (!usbd->open(VID, PID))
        return false;
    return true;
}

void Comm::close()
{
    usbd->close();
}

void Comm::test(const QString &str)
{
}
