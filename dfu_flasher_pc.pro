#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T11:22:31
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = dfu_flasher_pc
TEMPLATE = app


SOURCES += main.cpp\
	 mainwindow.cpp \
    comm.cpp \
    usb/usbd.cpp \
    usb/dfud.cpp

HEADERS  += mainwindow.h \
    comm.h \
    common.h \
    config.h \
    delay.h \
    error.h \
    usb/usbd.h \
    usb/dfu.h \
    usb/usb.h \
    usb/dfud.h \
    proto.h

FORMS    += mainwindow.ui

linux*{
LIBS += -ludev -lusb-1.0
DEFINES += HAVE_LIBUDEV
}

win32*{
LIBS += -lsetupapi -lusb-1.0
}

CONFIG += exceptions
