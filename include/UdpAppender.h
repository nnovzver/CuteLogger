/*
  Copyright (c) 2016 Vladimir Ruzanov (nnovzver at gmail dot com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1
  as published by the Free Software Foundation and appearing in the file
  LICENSE.LGPL included in the packaging of this file.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
*/
#ifndef UDPAPPENDER_H
#define UDPAPPENDER_H

#include "CuteLogger_global.h"
#include <AbstractStringAppender.h>
#include <QHostAddress>
#include <QUdpSocket>

class CUTELOGGERSHARED_EXPORT UdpAppender : public AbstractStringAppender
{
  public:
    UdpAppender(const QHostAddress &address, quint16 port);
    virtual QString format() const;
    void ignoreEnvironmentPattern(bool ignore);

  protected:
    virtual void append(const QDateTime& timeStamp, Logger::LogLevel logLevel, const char* file, int line,
                        const char* function, const QString& category, const QString& message);

  private:
    bool m_ignoreEnvPattern;
    QHostAddress m_addr;
    quint16 m_port;
    QUdpSocket m_sock;
};

#endif // UDPAPPENDER_H
