/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

const QString LOG_FILE_NAME("file.log");
const QString LOG_DATE_FORMAT("dd.MM hh:mm:ss.zzz");

const int PORT_DEFAULT_TIMEOUT =                                    5000;
const unsigned int VID =                                            0xABBA;
const unsigned int PID =                                            0xF001;

const unsigned int DFU_BLOCK_SIZE =                                 128;
const int REFRESH_RATE =                                            10;

#endif // CONFIG_H
