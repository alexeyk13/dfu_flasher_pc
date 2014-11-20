/*
    USB DFU Flasher PC part (cross-platform)
    Copyright (c) 2014, Alexey Kramarenko
    All rights reserved.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comm.h"
#include <QTextStream>
#include <QDateTime>
#include "config.h"
#include "error.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logFile(LOG_FILE_NAME),
    newLine(true)
{
    ui->setupUi(this);
    if (logFile.open(QIODevice::Append | QIODevice::Text))
        logToFile(tr("System started\n"));
    else
        logToScreen(tr("Can't create log\n"), Qt::darkYellow);
    comm = new Comm(this);
    connect(comm, SIGNAL(log(LOG_TYPE,QString,QColor)), this, SLOT(log(LOG_TYPE,QString,QColor)));
    info(tr("Application started\n"));
}

MainWindow::~MainWindow()
{
    delete comm;
    logFile.close();
    delete ui;
}

void MainWindow::logToScreen(const QString &text, const QColor &color)
{
    ui->log->setDisabled(true);
    ui->log->moveCursor(QTextCursor::End);
    QString html(QString("<font color=#%1>%2</font>").arg(static_cast<unsigned long>(color.rgb()) & 0xffffff, 6, 16, QChar('0')).arg(text));
    html.replace("\n", "<br>");
    ui->log->textCursor().insertHtml(html);
    ui->log->setDisabled(false);
}

void MainWindow::logToFile(const QString &text)
{
    if (logFile.isOpen())
    {
        QTextStream out(&logFile);
        if (newLine)
            out << QDateTime::currentDateTime().toString(LOG_DATE_FORMAT) << ' ';
        out << text;
        newLine = text.contains('\n');
    }
}

void MainWindow::log(LOG_TYPE type, const QString &text, const QColor &color)
{
    switch (type)
    {
    case LOG_TYPE_DEFAULT:
        logToScreen(text, color);
        logToFile(text);
        break;
    case LOG_TYPE_HINT:
        logToScreen(text, Qt::darkCyan);
        logToFile(tr("Hint: ") + text);
        break;
    case LOG_TYPE_WARNING:
        logToScreen(text, Qt::darkYellow);
        logToFile(tr("Warning: ") + text);
        break;
    case LOG_TYPE_ERROR:
        logToScreen(text, Qt::red);
        logToFile(tr("Error: ") + text);
        break;
    case LOG_TYPE_DEBUG:
#ifndef QT_NO_DEBUG
        logToScreen(text, Qt::lightGray);
#endif
        logToFile("> " + text);
        break;
    }
}

void MainWindow::flash()
{
//    if
//    info(comm->open() ? tr("USB DFU device connected\n") : tr("USB DFU device not found\n"));
}

void MainWindow::on_bFlash_clicked()
{
    try
    {
        if (comm->open())
        {
            info(tr("USB DFU device connected\n"));
            try
            {
                flash();
                comm->close();
            }
            catch (...)
            {
                comm->close();
                throw;
            }
        }
        else
            warning(tr("USB DFU device not found\n"));
    }
    catch (Exception& e)
    {
        info("here\n");
        error(e.what() + "\n");
    }
    catch (...)
    {
        error(tr("Unhandled exception\n"));
    }
}
