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

#include "sessionclient.h"


#include "botsettings.h"


#include "userdatabase.h"


#include "commandresolver.h"

#include <QDebug>
#include <QRegExp>

namespace
{
    const QString CMD_NICK              = "/nick";
    const QString CMD_JOIN              = "/join";
    const QString CMD_LEAVE             = "/leave";

    const QString MSG_NICK_EXIST        = "Uzytkownik o takim nicku juz istnieje!";
}

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
        QString command = rx.cap(1);
        if(command == CMD_NICK)
        {
            lastString = removeCommand(str, CMD_NICK);
            nickCommand();
            return true;
        }
        else if(command == CMD_JOIN)
        {
            lastString = removeCommand(str, CMD_JOIN);
            joinCommand();
            return true;
        }
        else if(command == CMD_LEAVE)
        {
            lastString = removeCommand(str, CMD_LEAVE);
            leaveCommand();
            return true;
        }
    }

    return false;
}

QString CommandResolver::removeCommand(QString message, QString command)
{
    QString ret = message.right(message.size()-command.size());
    return ret.simplified();
}

void CommandResolver::nickCommand()
{
    if(lastString.isEmpty())
        return;
    
    QRegExp rx("^(\\w+).*");
    int pos = 0;

    if((pos = rx.indexIn(lastString, pos)) != -1)
    {
        QString newNick = rx.cap(1);
        UserInfoTOPtr user = GetProfile()->getUserDatabase()->getUserInfo(m_event->event.msg.sender);

        QList<UserInfoTOPtr> users = GetProfile()->getUserDatabase()->getUserList();
        foreach(UserInfoTOPtr u, users)
        {
            if(u->getNick() == newNick)
            {
                GetProfile()->getSession()->sendMessageTo(user->getUin(), MSG_NICK_EXIST);
                return;
            }
        }

        QString debugMessage = QString("%1 %2 zmienil nick na %3").arg(user->getUin()).arg(user->getNick()).arg(newNick);
        qDebug() << debugMessage;
        GetProfile()->getSession()->sendMessageToSuperUser(user->getUin(), debugMessage);
        user->setNick(newNick);
        GetProfile()->getUserDatabase()->saveDatabase();
    }
}

void CommandResolver::joinCommand()
{
    UserInfoTOPtr user = GetProfile()->getUserDatabase()->getUserInfo(m_event->event.msg.sender);
    if(user->getOnChannel())
        return;

    user->setOnChannel(true);
    GetProfile()->getUserDatabase()->saveDatabase();
    QString msg = "Przychodzi " + user->getNick();
    qDebug() << msg;
    GetProfile()->getSession()->sendMessage(msg);
}

void CommandResolver::leaveCommand()
{
    UserInfoTOPtr user = GetProfile()->getUserDatabase()->getUserInfo(m_event->event.msg.sender);
    if(!user->getOnChannel())
        return;

    QString reason;
    if(!lastString.isEmpty())
    {
        reason = lastString;
    }

    user->setOnChannel(false);
    GetProfile()->getUserDatabase()->saveDatabase();
    QString msg = "Odchodzi " + user->getNick() + " " + reason;
    qDebug() << msg;
    GetProfile()->getSession()->sendMessage(msg);
}

