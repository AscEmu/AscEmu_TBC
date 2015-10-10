/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>
 * Copyright (C) 2008-2012 ArcEmu Team <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WOWSERVER_LOG_H
#define WOWSERVER_LOG_H

#include "Common.h"
#include "Singleton.h"

class WorldPacket;
class WorldSession;

#define TIME_FORMAT "[%H:%M:%S]"
#define TIME_FORMAT_LENGTH 100

#ifdef WIN32

#define TRED FOREGROUND_RED | FOREGROUND_INTENSITY
#define TGREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define TYELLOW FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define TNORMAL FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE
#define TWHITE TNORMAL | FOREGROUND_INTENSITY
#define TBLUE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY

#else

#define TRED 1
#define TGREEN 2
#define TYELLOW 3
#define TNORMAL 4
#define TWHITE 5
#define TBLUE 6

#endif

enum LogType
{
    WORLD_LOG,
    LOGON_LOG
};

extern SERVER_DECL time_t UNIXTIME;        //update this every loop to avoid the time() syscall!
extern SERVER_DECL tm g_localTime;

std::string FormatOutputString(const char * Prefix, const char * Description, bool useTimeStamp);

class SERVER_DECL oLog : public Singleton< oLog > {
public:
  void outString( const char * str, ... );
  void outError( const char * err, ... );
  void outErrorSilent(const char* err, ...);      // Writes into the error log without giving console output. Used for the startup banner.
  void outBasic( const char * str, ... );
  void outDetail( const char * str, ... );
  void outDebug( const char * str, ... );
  void outMenu( const char * str, ... );

  void logError(const char* file, int line, const char* fncname, const char* msg, ...);
  void logDebug(const char* file, int line, const char* fncname, const char* msg, ...);
  void logBasic(const char* file, int line, const char* fncname, const char* msg, ...);
  void logDetail(const char* file, int line, const char* fncname, const char* msg, ...);

  void fLogText(const char *text);
  void SetLogging(bool enabled);
  
  void Init(int32 fileLogLevel, LogType logType);
  void Close();
  void SetFileLoggingLevel(int32 level);
  void SetScreenLoggingLevel(int32 level);

  //NGLog.h stuff
  void Success(const char* source, const char* format, ...); //
  void Error(const char* source, const char* format, ...); //
  void LargeErrorMessage(const char* str, ...); //
  void Notice(const char* source, const char* format, ...);
  void Warning(const char* source, const char* format, ...);
  void Debug(const char* source, const char* format, ...); //

  int32 m_fileLogLevel;
  int32 m_screenLogLevel;

private:

    FILE* m_normalFile, *m_errorFile;
    void outFile(FILE* file, char* msg, const char* source = NULL);
    void outFileSilent(FILE* file, char* msg, const char* source = NULL);   // Prints text to file without showing it to the user. Used for the startup banner.
    void Time(char* buffer);
    void SetColor(int color);

#ifdef WIN32
  HANDLE stdout_handle, stderr_handle;
#endif

  inline char dcd(char in)
  {
      char out = in;
      out -= 13;
      out ^= 131;
      return out;
  }

  void dcds(char* str)
  {
      unsigned long i = 0;
      size_t len = strlen(str);

      for (i = 0; i < len; ++i)
          str[i] = dcd(str[i]);

  }

  void pdcds(const char* str, char* buf)
  {
      strcpy(buf, str);
      dcds(buf);
  }
};

class SessionLogWriter
{
	FILE * m_file;
	char * m_filename;
public:
	SessionLogWriter(const char * filename, bool open);
	~SessionLogWriter();

	void write(const char* format, ...);
	void writefromsession(WorldSession* session, const char* format, ...);
	inline bool IsOpen() { return (m_file != NULL); }
	void Open();
	void Close();
};



#define sLog oLog::getSingleton()

#define LOG_BASIC(msg, ...) sLog.logBasic(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)
#define LOG_DETAIL(msg, ...) sLog.logDetail(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) sLog.logError(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) sLog.logDebug(__FILE__, __LINE__, __FUNCTION__, msg, ##__VA_ARGS__)

#define Log sLog

class WorldLog : public Singleton<WorldLog>
{
public:
	WorldLog();
	~WorldLog();

	void LogPacket(uint32 len, uint16 opcode, const uint8* data, uint8 direction);
	void Enable();
	void Disable();
private:
	FILE * m_file;
	Mutex mutex;
	bool bEnabled;
};

#define sWorldLog WorldLog::getSingleton()

#endif

