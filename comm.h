/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QColor>
#include "common.h"

class USBD;

class Comm : public QObject
{
    Q_OBJECT
private:
    USBD* usbd;

protected:
    void info(const QString& text, const QColor& color = Qt::black) {log(LOG_TYPE_DEFAULT, text, color);}
    void hint(const QString& text) {log(LOG_TYPE_HINT, text, Qt::black);}
    void warning(const QString& text) {log(LOG_TYPE_WARNING, text, Qt::black);}
    void error(const QString& text) {log(LOG_TYPE_ERROR, text, Qt::black);}
    void debug(const QString& text) {log(LOG_TYPE_DEBUG, text, Qt::black);}

public:
    explicit Comm(QObject *parent = 0);
    virtual ~Comm();

    bool isActive();
    bool open();
    void close();
    void test(const QString& str);

signals:
    void log(LOG_TYPE type, const QString& text, const QColor& color);


public slots:

};

#endif // COMM_H
