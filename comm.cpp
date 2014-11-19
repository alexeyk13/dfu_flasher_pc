/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "comm.h"
#include "usb/usb.h"
#include "config.h"
#include "error.h"

Comm::Comm(QObject *parent) :
    QObject(parent)
{
    usb = new Usb();
}

Comm::~Comm()
{
    delete usb;
}

bool Comm::isConnected()
{
    return false;
}

bool Comm::connect()
{
    return false;
}

void Comm::disconnect()
{
}

void Comm::test(const QString &str)
{
}
