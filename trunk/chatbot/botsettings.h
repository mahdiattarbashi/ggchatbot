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

#ifndef _BOTSETTINGS_H
#define	_BOTSETTINGS_H

#include <QSettings>
#include <QtDebug>
#include <boost/shared_ptr.hpp>
#include "botsettingsto.h"

typedef boost::shared_ptr<QSettings> SettingsPtr;

class BotSettings
{
public:
    BotSettings();
    virtual ~BotSettings();
    void ReadBotSettings();
    void SaveBotSettings();

    BotSettingsTO getBotSettings() { return m_botSettings; }
private:
    SettingsPtr settings;
    BotSettingsTO m_botSettings;
};

#endif	/* _BOTSETTINGS_H */

