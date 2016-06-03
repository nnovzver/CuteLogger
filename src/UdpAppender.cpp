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
// Local
#include "UdpAppender.h"


/**
 * \class UdpAppender
 *
 * \brief UdpAppender is like ConsoleAppender but send udp message
 */


UdpAppender::UdpAppender(const QHostAddress & address, quint16 port)
  : AbstractStringAppender(),
    m_ignoreEnvPattern(false),
    m_addr(address),
    m_port(port)
{
  setFormat("[%{type:-7}] <%{function}> %{message}\n");
}


QString UdpAppender::format() const
{
  const QString envPattern = QString::fromLocal8Bit(qgetenv("QT_MESSAGE_PATTERN"));
  return (m_ignoreEnvPattern || envPattern.isEmpty()) ? AbstractStringAppender::format() : (envPattern + "\n");
}


void UdpAppender::ignoreEnvironmentPattern(bool ignore)
{
  m_ignoreEnvPattern = ignore;
}


//! Writes the log record to the udp socket
/**
 * \sa AbstractStringAppender::format()
 */
void UdpAppender::append(const QDateTime& timeStamp, Logger::LogLevel logLevel, const char* file, int line,
                             const char* function, const QString& category, const QString& message)
{
  QString m = formattedString(timeStamp, logLevel, file, line, function, category, message);
  QByteArray bytes = m.toUtf8();
  m_sock.writeDatagram(qPrintable(m), bytes.size(), m_addr, m_port);
}
