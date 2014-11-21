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
    QByteArray buf(sizeof(PROTO_REQ), 0);
    PROTO_REQ* proto = reinterpret_cast<PROTO_REQ*>(buf.data());
    proto->cmd = cmd;
    proto->data_size = data.size();
    proto->param1 = param1;
    proto->param2 = param2;
    dfud->write(buf + data);
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

QByteArray Comm::cmdRead(unsigned int addr, unsigned int size)
{
    cmdReq(PROTO_CMD_READ, addr, size);
    QByteArray buf(dfud->read());
    if (static_cast<unsigned int>(buf.size()) < size)
        throw ErrorProtocolInvalidResponse();
    return buf;
}

void Comm::cmdWrite(unsigned int addr, const QByteArray &buf)
{
    cmdReq(PROTO_CMD_WRITE, addr, buf.size(), buf);
}

void Comm::cmdErase(unsigned int addr, unsigned int size)
{
    cmdReq(PROTO_CMD_ERASE, addr, size);
}
