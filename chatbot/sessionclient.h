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

#ifndef _SESSIONCLIENT_H
#define	_SESSIONCLIENT_H

#include <QtCore>
#include <QSettings>
#include <QtDebug>
#include <boost/shared_ptr.hpp>
#include "libgadu.h"
#include "eventmanager.h"
#include "profilebase.h"

typedef boost::shared_ptr<QSettings> SettingsPtr;
typedef boost::shared_ptr<gg_session*> SessionPtr;
typedef boost::shared_ptr<gg_event*> EventPtr;

class SessionClient : public QObject, public ProfileBase
{
    Q_OBJECT
public:
    SessionClient();
    ~SessionClient();

    void MakeConnection();

signals:
    void endServer();
    
private:
    struct gg_login_params loginParams;
    struct gg_recv_msg gotmsg;
    struct gg_session *session;
    struct gg_event *event;
    SettingsPtr settings;
    EventManager eventManager;

    int m_level;
    uin_t m_uin;
    QString m_password;
    QString m_defaultDescription;

    void ReadSettings();
    void SaveSettings();
    void FreeSession(gg_session *session);
    void Logout(gg_session *session);
    void CleanEndExit();
    void SetDebugLevel();
    bool Login();
    bool SendContactList();
    void ChangeStatus(QString description = "v0.3", int status = GG_STATUS_AVAIL_DESCR);
    bool WaitForEvent();
    void EventLoop();
};

#endif	/* _SESSIONCLIENT_H */

