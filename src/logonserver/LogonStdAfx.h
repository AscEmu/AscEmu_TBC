/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2008 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "Log.h"
#include "Util.h"
#include "ByteBuffer.h"
#include "Config/ConfigEnv.h"
#include <zlib.h>

#include "Database/DatabaseEnv.h"
#include "Database/DBCStores.h"
#include "Database/dbcfile.h"

#include "Auth/BigNumber.h"
#include "Auth/Sha1.h"
#include "Auth/WowCrypt.h"
#include "CrashHandler.h"

#include "LogonOpcodes.h"
#include "Main.h"
#include "NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "AutoPatcher.h"
#include "AuthSocket.h"
#include "AuthStructs.h"
//#include "../arcemu-logonserver/LogonOpcodes.h"
#include "LogonCommServer.h"
#include "LogonConsole.h"
#include "WorldPacket.h"

// database decl
extern Database* sLogonSQL;
