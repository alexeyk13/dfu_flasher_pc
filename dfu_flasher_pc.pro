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
    usb/dfu/usb_dfu.cpp \
    usb/usbd.cpp

HEADERS  += mainwindow.h \
    comm.h \
    common.h \
    usb/dfu/usb_dfu_defs.h \
    usb/dfu/usb_dfu_error.h \
    usb/dfu/usb_dfu.h \
    config.h \
    delay.h \
    error.h \
    usb/usbd.h \
    usb/dfu.h \
    usb/usb.h

FORMS    += mainwindow.ui

linux*{
LIBS += -ludev -lusb-1.0
DEFINES += HAVE_LIBUDEV
}

win32*{
LIBS += -lsetupapi -lusb-1.0
}

CONFIG += exceptions
