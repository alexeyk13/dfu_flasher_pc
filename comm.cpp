/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "comm.h"
#include "usb/dfud.h"
#include "config.h"
#include "error.h"

Comm::Comm(QObject *parent) :
    QObject(parent)
{
    dfud = new DFUD();
}

Comm::~Comm()
{
    delete dfud;
}

bool Comm::isActive()
{
    return dfud->isActive();
}

bool Comm::open()
{
    if (!dfud->open(VID, PID))
        return false;
    info("DFU test\n");
    hint(QString("DFU status: %1\n").arg(dfud->test()));
    info("DFU test ok\n");

    info("DFU test write\n");
    dfud->write(QString("test").toLocal8Bit());
    hint(QString("DFU status: %1\n").arg(dfud->test()));
    info("DFU test write ok\n");
    return true;
}

void Comm::close()
{
    dfud->close();
}

void Comm::test(const QString &str)
{
}
