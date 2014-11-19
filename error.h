/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <QString>
#include <QObject>

/* base */
class Exception
{
public:
    Exception() throw() {}
    virtual ~Exception() throw() {}
    virtual QString what() throw() {return QObject::tr("Internal error");}
};

class ErrorNotActive: public Exception
{
    virtual QString what() throw() {return QObject::tr("Not active");}
};

/* cancel class */
class ErrorCancel: public Exception
{
    virtual QString what() throw() {return QObject::tr("Action cancelled");}
};

/* file errors */
class ErrorFile: public Exception
{
    virtual QString what() throw() {return QObject::tr("Generic file error");}
};

class ErrorFileNotFound: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File not found");}
};

class ErrorFileOpen: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File open error");}
};

class ErrorFileCreate: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File create error");}
};

class ErrorFileWrite: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File write error");}
};

class ErrorFileRead: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File read error");}
};

class ErrorFileCrc: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File crc error");}
};

class ErrorFileCopy: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File copy error");}
};

class ErrorFileRemove: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("File remove error");}
};

class ErrorFolderOpen: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("Folder open error");}
};

class ErrorFolderRemove: public ErrorFile
{
    virtual QString what() throw() {return QObject::tr("Folder remove error");}
};

/* network errors */
class ErrorNetwork: public Exception
{
    virtual QString what() throw() {return QObject::tr("Generic network error");}
};

class ErrorNetworkNotAccessible: public ErrorNetwork
{
    virtual QString what() throw() {return QObject::tr("Network is not accessible");}
};

class ErrorNetworkAuthenticationRequired: public ErrorNetwork
{
    virtual QString what() throw() {return QObject::tr("Authentication required");}
};

class ErrorNetworkForbidden: public ErrorNetwork
{
    virtual QString what() throw() {return QObject::tr("Forbidden");}
};

class ErrorNetworkOther: public ErrorNetwork
{
private:
    int code;
public:
    ErrorNetworkOther(int code) throw() : ErrorNetwork(), code(code) {}
    virtual QString what() throw() {return QString(QObject::tr("Generic network error: %1")).arg(code); }
};

#endif // ERROR_H
