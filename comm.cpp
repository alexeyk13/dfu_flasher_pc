/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "comm.h"
#include "usb/dfud.h"
#include "config.h"
#include "error.h"
#include "proto.h"

Comm::Comm(QObject *parent) :
    QObject(parent)
{
    dfud = new DFUD();
}

Comm::~Comm()
{
    delete dfud;
}

void Comm::cmdReq(unsigned char cmd, unsigned int param1, unsigned int param2, QByteArray data)
{
    QByteArray buf(sizeof(PROTO_REQ) + data.size(), 0);
    PROTO_REQ* proto = reinterpret_cast<PROTO_REQ*>(buf.data());
    proto->cmd = cmd;
    proto->param1 = param1;
    proto->param2 = param2;
    dfud->write(buf);
}

bool Comm::isActive()
{
    return dfud->isActive();
}

bool Comm::open()
{
    if (!dfud->open(VID, PID))
        return false;
    return true;
}

void Comm::close()
{
    dfud->close();
}

void Comm::cmdVersion(int& loader, int& protocol)
{
    cmdReq(PROTO_CMD_VERSION, 0, 0);
    QByteArray buf(dfud->read());
    if (static_cast<unsigned int>(buf.size()) < sizeof(PROTO_VERSION_RESP))
        throw ErrorProtocolInvalidResponse();
    PROTO_VERSION_RESP* version = reinterpret_cast<PROTO_VERSION_RESP*>(buf.data());
    loader = version->loader;
    protocol = version->protocol;
}

void Comm::cmdLeave()
{
    cmdReq(PROTO_CMD_LEAVE, 0, 0);
}

void Comm::test(const QString &str)
{

/*    info("DFU test read\n");
    hint(QString::fromLocal8Bit(dfud->read()).append("\n"));
    hint(QString("DFU status: %1\n").arg(dfud->test()));
    info("DFU test read ok\n");*/
}
