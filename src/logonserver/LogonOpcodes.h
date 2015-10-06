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

#ifndef __LOGONOPCODES_H
#define __LOGONOPCODES_H

enum RealmListOpcodes
{
	// Initialization of server/client connection...
	RCMSG_REGISTER_REALM						= 1,
	RSMSG_REALM_REGISTERED						= 2,

	// Upon client connect (for WS)
	RCMSG_REQUEST_SESSION						= 3,
	RSMSG_SESSION_RESULT						= 4,

	// Ping/Pong
	RCMSG_PING									= 5,
	RSMSG_PONG									= 6,

	// SQL Query Execute
	RCMSG_SQL_EXECUTE							= 7,
	RCMSG_RELOAD_ACCOUNTS						= 8,

	// Authentication
	RCMSG_AUTH_CHALLENGE						= 9,
	RSMSG_AUTH_RESPONSE							= 10,

	// Character->Account Transmission
	RSMSG_REQUEST_ACCOUNT_CHARACTER_MAPPING		= 11,
	RCMSG_ACCOUNT_CHARACTER_MAPPING_REPLY		= 12,

	// Update Character->Account Mapping
	RCMSG_UPDATE_CHARACTER_MAPPING_COUNT		= 13,
	RSMSG_DISCONNECT_ACCOUNT					= 14,

	// Console auth
	RCMSG_TEST_CONSOLE_LOGIN					= 15,
	RSMSG_CONSOLE_LOGIN_RESULT					= 16,

	// DB modifying
	RCMSG_MODIFY_DATABASE						= 17,

	// count
	RMSG_COUNT,
};

enum LogonRealmOpcodes
{
    LRCMSG_REALM_REGISTER_REQUEST     = 0x001,  // try register our realm
    LRSMSG_REALM_REGISTER_RESULT      = 0x002,  // register result from logonserver
    LRCMSG_ACC_SESSION_REQUEST        = 0x003,
    LRSMSG_ACC_SESSION_RESULT         = 0x004,
    LRCMSG_LOGON_PING_STATUS          = 0x005,  // request logon online
    LRSMSG_LOGON_PING_RESULT          = 0x006,  // send result if logon is online
    LRCMSG_FREE_01                    = 0x007,  // unused
    LRSMSG_FREE_02                    = 0x008,  // unused
    LRCMSG_AUTH_REQUEST               = 0x009,  // try authenticate our realm
    LRSMSG_AUTH_RESPONSE              = 0x00A,  // authentication result from logonserver
    LRSMSG_ACC_CHAR_MAPPING_REQUEST   = 0x00B,
    LRCMSG_ACC_CHAR_MAPPING_RESULT    = 0x00C,
    LRCMSG_ACC_CHAR_MAPPING_UPDATE    = 0x00D,
    LRSMSG_SEND_ACCOUNT_DISCONNECT    = 0x00E,  // send when account is disconnected
    LRCMSG_LOGIN_CONSOLE_REQUEST      = 0x00F,
    LRSMSG_LOGIN_CONSOLE_RESULT       = 0x010,
    LRCMSG_ACCOUNT_DB_MODIFY_REQUEST  = 0x011,  // request logon db change
    LRSMSG_ACCOUNT_DB_MODIFY_RESULT   = 0x012,
    LRSMSG_REALM_POPULATION_REQUEST   = 0x013,
    LRCMSG_REALM_POPULATION_RESULT    = 0x014,
    LRCMSG_ACCOUNT_REQUEST            = 0x015,  // request account data
    LRSMSG_ACCOUNT_RESULT             = 0x016,  // send account information to realm

    LRMSG_MAX_OPCODES                           // max opcodes
};

enum AccountDatabaseMethod
{
    Method_Account_Ban = 1,
    Method_Account_Set_GM,
    Method_Account_Set_Mute,
    Method_IP_Ban,
    Method_IP_Unban,
    Method_Account_Change_PW,
    Method_Account_Create
};

enum AccountDatabaseResult
{
    Result_Account_PW_wrong = 1,
    Result_Account_SQL_error,
    Result_Account_Finished,
    Result_Account_Exists
};

#endif
