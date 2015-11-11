/*
 * AscEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008 <http://www.AscEmu.org/>
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

#include "StdAfx.h"

#define BANNER "<< AscEmu %s/%s-%s (%s) :: World Server >>"

#ifndef WIN32
#include <sched.h>
#endif

#include "git_version.h"

#include <signal.h>

createFileSingleton( Master );
std::string LogFileName;
bool bLogChat;
bool crashed = false;

volatile bool Master::m_stopEvent = false;

// Database defines.
SERVER_DECL Database* Database_Character;
SERVER_DECL Database* Database_World;

// mainserv defines
SessionLogWriter* GMCommand_Log;
SessionLogWriter* Anticheat_Log;
SessionLogWriter* Player_Log;

// threads
extern DayWatcherThread * dw;
extern CommonScheduleThread * cs;

void Master::_OnSignal(int s)
{
	switch (s)
	{
#ifndef WIN32
	case SIGHUP:
		sWorld.Rehash(true);
		break;
#endif
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
#ifdef _WIN32
	case SIGBREAK:
#endif
		Master::m_stopEvent = true;
		break;
	}

	signal(s, _OnSignal);
}

Master::Master()
{
	m_ShutdownTimer = 0;
	m_ShutdownEvent = false;
	m_restartEvent = false;
}

Master::~Master()
{
}

struct Addr
{
	unsigned short sa_family;
	/* sa_data */
	unsigned short Port;
	unsigned long IP; // inet_addr
	unsigned long unusedA;
	unsigned long unusedB;
};

#define DEF_VALUE_NOT_SET 0xDEADBEEF


static const char* default_config_file = CONFDIR "/world.conf";
static const char* default_optional_config_file = CONFDIR "/optional.conf";
static const char* default_realm_config_file = CONFDIR "/realms.conf";


bool bServerShutdown = false;
bool StartConsoleListener();
void CloseConsoleListener();
ThreadBase * GetConsoleListener();

bool Master::Run(int argc, char ** argv)
{
	char * config_file = (char*)default_config_file;
	char * optional_config_file = (char*)default_optional_config_file;
	char * realm_config_file = (char*)default_realm_config_file;

	int file_log_level = DEF_VALUE_NOT_SET;
	int screen_log_level = DEF_VALUE_NOT_SET;
	int do_check_conf = 0;
	int do_version = 0;
	int do_cheater_check = 0;
	int do_database_clean = 0;
	time_t curTime;

	struct AscEmu_option longopts[] =
	{
		{ "checkconf",			AscEmu_no_argument,				&do_check_conf,			1		},
		{ "screenloglevel",		AscEmu_required_argument,		&screen_log_level,		1		},
		{ "fileloglevel",		AscEmu_required_argument,		&file_log_level,		1		},
		{ "version",			AscEmu_no_argument,				&do_version,			1		},
		{ "conf",				AscEmu_required_argument,		NULL,					'c'		},
		{ "realmconf",			AscEmu_required_argument,		NULL,					'r'		},
		{ "databasecleanup",	AscEmu_no_argument,				&do_database_clean,		1		},
		{ "cheatercheck",		AscEmu_no_argument,				&do_cheater_check,		1		},
		{ 0, 0, 0, 0 }
	};

	char c;
	while ((c = AscEmu_getopt_long_only(argc, argv, ":f:", longopts, NULL)) != -1)
	{
		switch (c)
		{
		case 'c':
			config_file = new char[strlen(AscEmu_optarg)];
			strcpy(config_file, AscEmu_optarg);
			break;

		case 'r':
			realm_config_file = new char[strlen(AscEmu_optarg)];
			strcpy(realm_config_file, AscEmu_optarg);
			break;

		case 0:
			break;
		default:
			sLog.m_fileLogLevel = -1;
			sLog.m_screenLogLevel = 3;
			printf("Usage: %s [--checkconf] [--screenloglevel <level>] [--fileloglevel <level>] [--conf <filename>] [--realmconf <filename>] [--version] [--databasecleanup] [--cheatercheck]\n", argv[0]);
			return true;
		}
	}

	// Startup banner
	UNIXTIME = time(NULL);
	g_localTime = *localtime(&UNIXTIME);

	if(!do_version && !do_check_conf)
	{
        sLog.Init(0, WORLD_LOG);
	}
	else
	{
		sLog.m_fileLogLevel = -1;
		sLog.m_screenLogLevel = 1;
	}

    sLog.outBasic(BANNER, BUILD_HASH_STR, CONFIG, PLATFORM_TEXT, ARCH);
    sLog.outBasic("========================================================");
    sLog.outErrorSilent(BANNER, BUILD_HASH_STR, CONFIG, PLATFORM_TEXT, ARCH); // Echo off.
    sLog.outErrorSilent("========================================================"); // Echo off.

    sLog.outBasic("Copyright (C) 2014 - 2015 AscEmu. http://www.ascemu.org/");
	sLog.outBasic("This program is free software: you can redistribute it and/or modify");
	sLog.outBasic("it under the terms of the GNU Affero General Public License as published by");
	sLog.outBasic("the Free Software Foundation, either version 3 of the License, or");
	sLog.outBasic("any later version.");
	sLog.outBasic("This program is distributed in the hope that it will be useful,");
	sLog.outBasic("but WITHOUT ANY WARRANTY; without even the implied warranty of");
	sLog.outBasic("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the");
	sLog.outBasic("GNU Affero General Public License for more details.");
	sLog.outBasic("                                                ");
	sLog.outBasic("                     ``````                     ");
	sLog.outBasic("    AscEmu!        `/o/::-:/-                   "); 
	sLog.outBasic("                   oho/-.-:yN-                  "); 
	sLog.outBasic("                    os+/-.:::                   "); 
	sLog.outBasic("                    :ysyoo+:`                   "); 
	sLog.outBasic("                    `ohdys/.                    "); 
	sLog.outBasic("                     oyho/-`   ``               "); 
	sLog.outBasic("                   `shyo+:./ssmdsyo:`           "); 
	sLog.outBasic("                    .shss+:yNMMNNMNmms.         "); 
	sLog.outBasic("                    :ysss+:mNMMMMNNmmds.        "); 
	sLog.outBasic("                `-//sssoo/:NMNMMMNMNNdy-        "); 
	sLog.outBasic("    -`/`       `omhyyhyyyshNMMNNNMMMNmy:        "); 
	sLog.outBasic("    :/::-`     `sdmdmmNMNMMMMMMNMNNNNms-        "); 
	sLog.outBasic("     /+++/-.....shdmmNMMNMMMMMMMMMNNNd+         ");
	sLog.outBasic("     ./+oshyhhhddmhdmNMMMMMMMMMMMMNNds.         "); 
	sLog.outBasic("       `:/:.`````.:+ymmNMMNMMMNMMNNd/           "); 
	sLog.outBasic("                     -+shmNNMMMNmhy/            "); 
	sLog.outBasic("                          `..-ods:.             ");
	sLog.outBasic("                               o:.`             ");
	sLog.outBasic("                               :-.              ");
	sLog.outBasic("                              `/-...            "); 
	sLog.outBasic("    Introducing the emu!     --``-/:`           "); 
	sLog.outBasic("                           .:/+:-.-::.          "); 
	sLog.outBasic("                          `.-///:-.`            ");
	sLog.outBasic(" Website: http://www.AscEmu.org                 ");
	sLog.outBasic(" Forums: http://www.board.ascemu.org/           ");
	sLog.outBasic(" GIT: https://github.com/AscEmu/AscEmu_TBC      ");
	sLog.outBasic(" Have fun!                                      ");

	if(do_version)
		return true;

	if( do_check_conf )
	{
		Log.Notice( "Config", "Checking config file: %s", config_file );
		if( Config.MainConfig.SetSource(config_file, true ) )
			Log.Success( "Config", "Passed without errors." );
		else
			Log.Warning( "Config", "Encountered one or more errors." );

		Log.Notice( "Config", "Checking config file: %s", realm_config_file );
		if( Config.RealmConfig.SetSource( realm_config_file, true ) )
			Log.Success( "Config", "Passed without errors." );
		else
			Log.Warning( "Config", "Encountered one or more errors." );

		Log.Notice( "Config", "Checking config file:: %s", optional_config_file);
		if(Config.OptionalConfig.SetSource(optional_config_file, true) )
			Log.Success( "Config", "Passed without errors.");
		else
			Log.Warning( "Config", "Encountered one or more errors.");

		return true;
	}

    sLog.outBasic("The key combination <Ctrl-C> will safely shut down the server at any time.");
    
#ifndef WIN32
	if(geteuid() == 0 || getegid() == 0)
		Log.LargeErrorMessage("You are running AscEmu as root.", "This is not needed, and may be a possible security risk.", "It is advised to hit CTRL+C now and", "start as a non-privileged user.", NULL);
#endif

	InitRandomNumberGenerators();
	Log.Success( "Rnd", "Initialized Random Number Generators." );

	ThreadPool.Startup();
	uint32 LoadingTime = getMSTime();

    Log.Success("Config", "Loading Config Files...");
    if (Config.MainConfig.SetSource(config_file))
        Log.Notice("Config", ">> " CONFDIR "/world.conf loaded");
    else
    {
        Log.Error("Config", ">> error occurred loading " CONFDIR "/world.conf");
        return false;
    }

    if (Config.OptionalConfig.SetSource(optional_config_file))
        Log.Notice("Config", ">> " CONFDIR "/optional.conf loaded");
    else
    {
        Log.Error("Config", ">> error occurred loading " CONFDIR "/optional.conf");
        return false;
    }


    if (Config.RealmConfig.SetSource(realm_config_file))
        Log.Notice("Config", ">> " CONFDIR "/realms.conf loaded");
    else
    {
        Log.Error("Config", ">> error occurred loading " CONFDIR "/realms.conf");
        return false;
    }

#if !defined(WIN32) && defined(__DEBUG__)
	if (Config.MainConfig.GetIntDefault( "LogLevel", "DisableCrashdumpReport", 0) == 0)
	{
		char cmd[1024];
		char banner[1024];
		snprintf(banner, 1024, BANNER, BUILD_TAG, BUILD_REVISION, CONFIG, PLATFORM_TEXT, ARCH);
		snprintf(cmd, 1024, "./crashreport -r %d -d \"%s\"", BUILD_REVISION, banner);
		system(cmd);
	}
	unlink("AscEmu.uptime");
#endif

	if( !_StartDB() )
	{
		Database::CleanupLibs();
        sLog.Close();
		return false;
	}

    // Checking the DB version. If it's wrong or can't be validated we exit.
    if (!CheckDBVersion())
    {
        sLog.Close();
        return false;
    }

	if(do_database_clean)
	{
        sLog.outDebug("Entering database maintenance mode." );
		new DatabaseCleaner;
		DatabaseCleaner::getSingleton().Run();
		delete DatabaseCleaner::getSingletonPtr();
        sLog.outDebug("Maintenance finished.");
	}

#ifdef GM_SCRIPT
	ScriptSystem = new ScriptEngine;
	ScriptSystem->Reload();
#endif

	new EventMgr;
	new World;
	//have to init this ones for singleton
	new tPPoolClass<Item>;
	new tPPoolClass<Aura>;
	new tPPoolClass<Spell>;

	// open cheat log file
	Anticheat_Log = new SessionLogWriter(FormatOutputString( "logs", "cheaters", false).c_str(), false );
	GMCommand_Log = new SessionLogWriter(FormatOutputString( "logs", "gmcommand", false).c_str(), false );
	Player_Log = new SessionLogWriter(FormatOutputString( "logs", "players", false).c_str(), false );

	/* load the config file */
	sWorld.Rehash(false);

	/* set new log levels */
	if( screen_log_level != (int)DEF_VALUE_NOT_SET )
		sLog.SetScreenLoggingLevel(screen_log_level);
	
	if( file_log_level != (int)DEF_VALUE_NOT_SET )
		sLog.SetFileLoggingLevel(file_log_level);

	// Initialize Opcode Table
	WorldSession::InitPacketHandlerTable();

    std::string host = Config.MainConfig.GetStringDefault("Listen", "Host", DEFAULT_HOST);
	int wsport = Config.MainConfig.GetIntDefault( "Listen", "WorldServerPort", DEFAULT_WORLDSERVER_PORT );

	new ScriptMgr;

	if( !sWorld.SetInitialWorldSettings() )
	{
		Log.Error( "Server", "SetInitialWorldSettings() failed. Something went wrong? Exiting." );
		return false;
	}

	if( do_cheater_check )
		sWorld.CleanupCheaters();

	sWorld.SetStartTime((uint32)UNIXTIME);
	
	WorldRunnable * wr = new WorldRunnable();
	ThreadPool.ExecuteTask(wr);

	_HookSignals();

	ConsoleThread * console = new ConsoleThread();
	ThreadPool.ExecuteTask(console);

	uint32 realCurrTime, realPrevTime;
	realCurrTime = realPrevTime = getMSTime();

	// Socket loop!
	uint32 start;
	uint32 diff;
	uint32 last_time = now();
	uint32 etime;
	uint32 next_printout = getMSTime(), next_send = getMSTime();

	// Start Network Subsystem
	Log.Notice( "Network","Starting subsystem..." );
	new SocketMgr;
	new SocketGarbageCollector;
	sSocketMgr.SpawnWorkerThreads();

	sScriptMgr.LoadScripts();

	LoadingTime = getMSTime() - LoadingTime;
	Log.Notice( "Server","Ready for connections. Startup time: %ums\n", LoadingTime );

	Log.Notice("RemoteConsole", "Starting...");
	if( StartConsoleListener() )
	{
#ifdef WIN32
		ThreadPool.ExecuteTask( GetConsoleListener() );
#endif
		Log.Notice("RemoteConsole", "Now open.");
	}
	else
	{
		Log.Warning("RemoteConsole", "Not enabled or failed listen.");
	}
	
 
	/* write pid file */
	FILE * fPid = fopen( "worldserver.pid", "w" );
	if( fPid )
	{
		uint32 pid;
#ifdef WIN32
		pid = GetCurrentProcessId();
#else
		pid = getpid();
#endif
		fprintf( fPid, "%u", (unsigned int)pid );
		fclose( fPid );
	}
#ifdef WIN32
	HANDLE hThread = GetCurrentThread();
#endif

	uint32 loopcounter = 0;
	//ThreadPool.Gobble();

#ifndef CLUSTERING
	/* Connect to realmlist servers / logon servers */
	new LogonCommHandler();
	sLogonCommHandler.Startup();

	/* voicechat */
#ifdef VOICE_CHAT
	new VoiceChatHandler();
	sVoiceChatHandler.Startup();
#endif

	// Create listener
	ListenSocket<WorldSocket> * ls = new ListenSocket<WorldSocket>(host.c_str(), wsport);
    bool listnersockcreate = ls->IsOpen();
#ifdef WIN32
	if( listnersockcreate )
		ThreadPool.ExecuteTask(ls);
#endif
	while( !m_stopEvent && listnersockcreate )
#else
	new ClusterInterface;
	sClusterInterface.ConnectToRealmServer();
	while(!m_stopEvent)
#endif
	{
		start = now();
		diff = start - last_time;
		if(! ((++loopcounter) % 10000) )		// 5mins
		{
			ThreadPool.ShowStats();
			ThreadPool.IntegrityCheck();
#if !defined(WIN32) && defined(__DEBUG__)
			FILE * f = fopen( "AscEmu.uptime", "w" );
			if( f )
			{
				fprintf(f, "%u", sWorld.GetUptime());
				fclose(f);
			}
#endif
		}

		/* since time() is an expensive system call, we only update it once per server loop */
		curTime = time(NULL);
		if( UNIXTIME != curTime )
		{
			UNIXTIME = time(NULL);
			g_localTime = *localtime(&curTime);
		}

#ifndef CLUSTERING
#ifdef VOICE_CHAT
		sVoiceChatHandler.Update();
#endif
#else
		sClusterInterface.Update();
#endif
		sSocketGarbageCollector.Update();

		/* UPDATE */
		last_time = now();
		etime = last_time - start;
		if( m_ShutdownEvent )
		{
			if( getMSTime() >= next_printout )
			{
				if(m_ShutdownTimer > 60000.0f)
				{
					if( !( (int)(m_ShutdownTimer) % 60000 ) )
						Log.Notice( "Server", "Shutdown in %i minutes.", (int)(m_ShutdownTimer / 60000.0f ) );
				}
				else
					Log.Notice( "Server","Shutdown in %i seconds.", (int)(m_ShutdownTimer / 1000.0f ) );
					
				next_printout = getMSTime() + 500;
			}

			if( getMSTime() >= next_send )
			{
				int time = m_ShutdownTimer / 1000;
				if( ( time % 30 == 0 ) || time < 10 )
				{
					// broadcast packet.
					WorldPacket data( 20 );
					data.SetOpcode( SMSG_SERVER_MESSAGE );
					if(m_restartEvent)
						data << uint32( SERVER_MSG_RESTART_TIME );
					else
						data << uint32( SERVER_MSG_SHUTDOWN_TIME );
					
					if( time > 0 )
					{
						int mins = 0, secs = 0;
						if(time > 60)
							mins = time / 60;
						if(mins)
							time -= (mins * 60);
						secs = time;
						char str[20];
						snprintf( str, 20, "%02u:%02u", mins, secs );
						data << str;
						sWorld.SendGlobalMessage( &data, NULL );
					}
				}
				next_send = getMSTime() + 1000;
			}
			if( diff >= m_ShutdownTimer )
				break;
			else
				m_ShutdownTimer -= diff;
		}

		if( 50 > etime )
		{
#ifdef WIN32
			WaitForSingleObject( hThread, 50 - etime );
#else
			Sleep( 50 - etime );
#endif
		}
	}
	_UnhookSignals();

    wr->SetThreadState( THREADSTATE_TERMINATE );
	ThreadPool.ShowStats();
	/* Shut down console system */
	console->terminate();
	delete console;

	// begin server shutdown
	Log.Notice( "Shutdown", "Initiated at %s", ConvertTimeStampToDataTime( (uint32)UNIXTIME).c_str() );

	if( lootmgr.is_loading )
	{
		Log.Notice( "Shutdown", "Waiting for loot to finish loading..." );
		while( lootmgr.is_loading )
			Sleep( 100 );
	}

	// send a query to wake it up if its inactive
	Log.Notice( "Database", "Clearing all pending queries..." );

	// kill the database thread first so we don't lose any queries/data
	CharacterDatabase.EndThreads();
	WorldDatabase.EndThreads();

	Log.Notice( "DayWatcherThread", "Exiting..." );
	dw->terminate();
	dw = NULL;

	Log.Notice( "CommonScheduleThread", "Exiting..." );
	cs->terminate();
	cs = NULL;

#ifndef CLUSTERING
	ls->Close();
#endif

	CloseConsoleListener();
	sWorld.SaveAllPlayers();

	Log.Notice( "Network", "Shutting down network subsystem." );
#ifdef WIN32
	sSocketMgr.ShutdownThreads();
#endif
	sSocketMgr.CloseAll();

	bServerShutdown = true;
	ThreadPool.Shutdown();

	delete ls;

	sWorld.LogoutPlayers();
	sLog.outString( "" );

	delete LogonCommHandler::getSingletonPtr();

	//should delete pools before other handlers !
	Log.Notice( "Item Pool", "Item Pool" );
	ItemPool.DestroyPool();

	Log.Notice( "Spell Pool", "Spell Pool" );
	SpellPool.DestroyPool();

	Log.Notice( "Aura Pool", "Aura Pool" );
	AuraPool.DestroyPool();

	sWorld.ShutdownClasses();
	Log.Notice( "World", "~World()" );
	delete World::getSingletonPtr();

	sScriptMgr.UnloadScripts();
	delete ScriptMgr::getSingletonPtr();

	Log.Notice( "ChatHandler", "~ChatHandler()" );
	delete ChatHandler::getSingletonPtr();

	Log.Notice( "EventMgr", "~EventMgr()" );
	delete EventMgr::getSingletonPtr();

	Log.Notice( "Database", "Closing Connections..." );
	_StopDB();

	Log.Notice( "Network", "Deleting Network Subsystem..." );
	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();
#ifdef VOICE_CHAT
	Log.Notice( "VoiceChatHandler", "~VoiceChatHandler()" );
	delete VoiceChatHandler::getSingletonPtr();
#endif

#ifdef GM_SCRIPT
	Log.Notice("GM-scripting:", "Closing ScriptEngine...");
	delete ScriptSystem;
#endif

#ifdef ENABLE_LUA_SCRIPTING
	sLog.outString("Deleting Script Engine...");
	LuaEngineMgr::getSingleton().Unload();
#endif

	delete GMCommand_Log;
	delete Anticheat_Log;
	delete Player_Log;

	// remove pid
	remove( "worldserver.pid" );

	Log.Notice( "Shutdown", "Shutdown complete." );

#ifdef WIN32
	WSACleanup();

	// Terminate Entire Application
	//HANDLE pH = OpenProcess(PROCESS_TERMINATE, TRUE, GetCurrentProcessId());
	//TerminateProcess(pH, 0);
	//CloseHandle(pH);

#endif

	return true;
}

static const char *REQUIRED_CHAR_DB_VERSION = "2015-11-10_01_character_db_version";
static const char *REQUIRED_WORLD_DB_VERSION = "2015-11-10_02_npc_script_text";

bool Master::CheckDBVersion()
{
    QueryResult* wqr = WorldDatabase.QueryNA("SELECT LastUpdate FROM world_db_version;");
    if (wqr == NULL)
    {
        Log.Error("Database", "World database is missing the table `world_db_version` OR the table doesn't contain any rows. Can't validate database version. Exiting.");
        Log.Error("Database", "You may need to update your database");
        return false;
    }

    Field* f = wqr->Fetch();
    const char *WorldDBVersion = f->GetString();

    Log.Notice("Database", "Last world database update: %s", WorldDBVersion);
    int result = strcmp(WorldDBVersion, REQUIRED_WORLD_DB_VERSION);
    if (result != 0)
    {
        Log.Error("Database", "Last world database update doesn't match the required one which is %s.", REQUIRED_WORLD_DB_VERSION);

        if (result < 0)
        {
            Log.Error("Database", "You need to apply the world update queries that are newer than %s. Exiting.", WorldDBVersion);
            Log.Error("Database", "You can find the world update queries in the sql/world_updates sub-directory of your AscEmu source directory.");
        }
        else
            Log.Error("Database", "Your world database is probably too new for this AscEmu version, you need to update your server. Exiting.");

        delete wqr;
        return false;
    }

    delete wqr;

    QueryResult* cqr = CharacterDatabase.QueryNA("SELECT LastUpdate FROM character_db_version;");
    if (cqr == NULL)
    {
        Log.Error("Database", "Character database is missing the table `character_db_version` OR the table doesn't contain any rows. Can't validate database version. Exiting.");
        Log.Error("Database", "You may need to update your database");
        return false;
    }

    f = cqr->Fetch();
    const char *CharDBVersion = f->GetString();

    Log.Notice("Database", "Last character database update: %s", CharDBVersion);
    result = strcmp(CharDBVersion, REQUIRED_CHAR_DB_VERSION);
    if (result != 0)
    {
        Log.Error("Database", "Last character database update doesn't match the required one which is %s.", REQUIRED_CHAR_DB_VERSION);
        if (result < 0)
        {
            Log.Error("Database", "You need to apply the character update queries that are newer than %s. Exiting.", CharDBVersion);
            Log.Error("Database", "You can find the character update queries in the sql/character_updates sub-directory of your AscEmu source directory.");
        }
        else
            Log.Error("Database", "Your character database is too new for this AscEmu version, you need to update your server. Exiting.");

        delete cqr;
        return false;
    }

    delete cqr;

    Log.Success("Database", "Database successfully validated.");

    return true;
}

bool Master::_StartDB()
{
	Database_World=NULL;
	Database_Character=NULL;
    std::string hostname, username, password, database;
	int port = 0;

	// Configure Main Database
	bool result = Config.MainConfig.GetString( "WorldDatabase", "Username", &username );
	Config.MainConfig.GetString( "WorldDatabase", "Password", &password );
	result = !result ? result : Config.MainConfig.GetString( "WorldDatabase", "Hostname", &hostname );
	result = !result ? result : Config.MainConfig.GetString( "WorldDatabase", "Name", &database );
	result = !result ? result : Config.MainConfig.GetInt( "WorldDatabase", "Port", &port );
	Database_World = Database::CreateDatabaseInterface();

	if(result == false)
	{
		Log.Error( "sql","One or more parameters were missing from WorldDatabase directive." );
		return false;
	}

	// Initialize it
	if( !WorldDatabase.Initialize(hostname.c_str(), (unsigned int)port, username.c_str(),
		password.c_str(), database.c_str(), Config.MainConfig.GetIntDefault( "WorldDatabase", "ConnectionCount", 3 ), 16384 ) )
	{
		Log.Error( "sql","Main database initialization failed. Exiting." );
		return false;
	}

	result = Config.MainConfig.GetString( "CharacterDatabase", "Username", &username );
	Config.MainConfig.GetString( "CharacterDatabase", "Password", &password );
	result = !result ? result : Config.MainConfig.GetString( "CharacterDatabase", "Hostname", &hostname );
	result = !result ? result : Config.MainConfig.GetString( "CharacterDatabase", "Name", &database );
	result = !result ? result : Config.MainConfig.GetInt( "CharacterDatabase", "Port", &port );
	Database_Character = Database::CreateDatabaseInterface();

	if(result == false)
	{
		Log.Error( "sql","One or more parameters were missing from Database directive." );
		return false;
	}

	// Initialize it
	if( !CharacterDatabase.Initialize( hostname.c_str(), (unsigned int)port, username.c_str(),
		password.c_str(), database.c_str(), Config.MainConfig.GetIntDefault( "CharacterDatabase", "ConnectionCount", 5 ), 16384 ) )
	{
		Log.Error( "sql","Main database initialization failed. Exiting." );
		return false;
	}

	return true;
}

void Master::_StopDB()
{
	if (Database_World != NULL)
	delete Database_World;
	if (Database_Character != NULL)
	delete Database_Character;
	Database::CleanupLibs();
}

void Master::_HookSignals()
{
	signal( SIGINT, _OnSignal );
	signal( SIGTERM, _OnSignal );
	signal( SIGABRT, _OnSignal );
#ifdef _WIN32
	signal( SIGBREAK, _OnSignal );
#else
	signal( SIGHUP, _OnSignal );
	signal(SIGUSR1, _OnSignal);
#endif
}

void Master::_UnhookSignals()
{
	signal( SIGINT, 0 );
	signal( SIGTERM, 0 );
	signal( SIGABRT, 0 );
#ifdef _WIN32
	signal( SIGBREAK, 0 );
#else
	signal( SIGHUP, 0 );
#endif

}

#ifdef WIN32

Mutex m_crashedMutex;

// Crash Handler
void OnCrash( bool Terminate )
{
		Log.Error( "Crash Handler","Advanced crash handler initialized." );

	if( !m_crashedMutex.AttemptAcquire() )
		TerminateThread( GetCurrentThread(), 0 );

	try
	{
		if( World::getSingletonPtr() != 0 )
		{
			Log.Notice( "sql","Waiting for all database queries to finish..." );
			WorldDatabase.EndThreads();
			CharacterDatabase.EndThreads();
			Log.Notice( "sql","All pending database operations cleared.\n" );
			sWorld.SaveAllPlayers();
			Log.Notice( "sql","Data saved." );
		}
	}
	catch(...)
	{
		Log.Error( "sql","Threw an exception while attempting to save all data." );
	}

	Log.Notice( "Server","Closing." );
	
	// beep
	//printf("\x7");
	
	// Terminate Entire Application
	if( Terminate )
	{
		HANDLE pH = OpenProcess( PROCESS_TERMINATE, TRUE, GetCurrentProcessId() );
		TerminateProcess( pH, 1 );
		CloseHandle( pH );
	}
}

#endif
