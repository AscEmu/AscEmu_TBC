#include "DatabaseEnv.h"
#include "../CrashHandler.h"
#include "../Log.h"

#if defined(ENABLE_DATABASE_MYSQL)
#include "MySQLDatabase.h"
#endif

void Database::CleanupLibs()
{
#if defined(ENABLE_DATABASE_MYSQL)
		mysql_library_end();
#endif
}


Database * Database::CreateDatabaseInterface(uint32 uType)
{
	switch(uType)
	{
#if defined(ENABLE_DATABASE_MYSQL)
	case 1:		// MYSQL
		return new MySQLDatabase();
		break;
#endif

	}

    Log.LargeErrorMessage("You have attempted to connect to a database that is unsupported or nonexistant.\nCheck your config and try again.", NULL);
	abort();
	return NULL;
}
