/*
    This file is part of GGChatBot.

    Copyright (C) 2009  Dariusz Mikulski <dariusz.mikulski@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.html>.
*/

#include "commandresolver.h"

#include <QDebug>
#include <QRegExp>

CommandResolver::CommandResolver()
{
}

CommandResolver::~CommandResolver()
{
}

bool CommandResolver::checkCommand(gg_event *event)
{
    m_event = event;
    
    QRegExp rx("^(/\\w+).*");
    QString str = QString::fromAscii((const char*)m_event->event.msg.message);
    int pos = 0;

    if((pos = rx.indexIn(str, pos)) != -1)
    {
        if(rx.cap(1) == "/nick")
        {
            qDebug() << rx.cap(0) << rx.cap(1);
            nickCommand();
            return true;
        }
    }

    return false;
}

void CommandResolver::nickCommand()
{
    
}

