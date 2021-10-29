#include "uartclass.h"
#include <qthread.h>
#include <stdint.h>

uartClass::uartClass()
{
    uartOpenStatus = false;

    foreach (const QSerialPortInfo &info , QSerialPortInfo::availablePorts()) {
        QSerialPort SerialPort;
        SerialPort.setPort(info);
        if(SerialPort.open(QIODevice::ReadWrite))
        {
            uartComAvailable.append(SerialPort.portName());
            SerialPort.close();
        }
    }
}


void uartClass::uartRefreshCOM()
{
    uartComAvailable.clear();
    foreach (const QSerialPortInfo &info , QSerialPortInfo::availablePorts()) {
        QSerialPort SerialPort;
        SerialPort.setPort(info);
        if(SerialPort.open(QIODevice::ReadWrite))
        {
            uartComAvailable.append(SerialPort.portName());
            SerialPort.close();
        }
    }
}


bool uartClass::uartOpenPort(const QString portName, uint32_t bps)
{
    if(uartOpenStatus)
    {
        return false;
    }
    uartPort.setPortName(portName);
    if(uartPort.open(QSerialPort::ReadWrite))
    {
        uartPort.setBaudRate(bps);
        uartOpenStatus = true;
    }
    return uartOpenStatus;
}



void uartClass::uartClosePort()
{
    if(uartOpenStatus)
    {
        uartOpenStatus = false;
        uartPort.close();
    }
}


void uartClass::uartSendBuff(uint8_t *pbuf, uint32_t len)
{
    if(uartOpenStatus)
    {
        uartPort.write((const char *)pbuf, len);
    }
}

uint32_t uartClass::uartReadBuff(uint8_t *pbuf)
{
    QByteArray readbuf;
    if(uartOpenStatus)
    {
        if(pbuf == NULL)
        {
            return 0;
        }
        int avail = uartPort.bytesAvailable();
        if (avail >= exp_recv_byte_num) {
            readbuf = uartPort.readAll();
            QString  str;
            str = "Available: " + QString::number(avail);
            qDebug(str.toStdString().c_str());
        }
        int actual = readbuf.length();
        if(actual > 0)
        {
            memcpy(pbuf, readbuf, readbuf.length());
            QString  str;
            str = "Actual: " + QString::number(actual);
            qDebug(str.toStdString().c_str());
        }
        return readbuf.length();
    }
    return 0;
}

bool uartClass::uartGetOpenStatus()
{
    return uartOpenStatus;
}
