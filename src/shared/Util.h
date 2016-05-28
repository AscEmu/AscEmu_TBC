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

#ifndef _UTIL_H
#define _UTIL_H

#include "Common.h"

///////////////////////////////////////////////////////////////////////////////
// String Functions ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> StrSplit(const std::string &src, const std::string &sep);

// This HAS to be called outside the threads __try / __except block!
void SetThreadName(const char* format, ...);
time_t convTimePeriod ( uint32 dLength, char dType);

extern SERVER_DECL const char* _StringToUTF8(const char*pASCIIBuf);
extern SERVER_DECL const char* _StringToANSI(const char*pUtf8Buf);
extern SERVER_DECL bool _IsStringUTF8(const char *str);

#ifdef WIN32

	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // must be 0x1000
		LPCSTR szName; // pointer to name (in user addr space)
		DWORD dwThreadID; // thread ID (-1=caller thread)
		DWORD dwFlags; // reserved for future use, must be zero
	} THREADNAME_INFO;

#endif

    namespace Arcemu
    {
        SERVER_DECL float round(float f);
        SERVER_DECL double round(double d);
        SERVER_DECL long double round(long double ld);

        /////////////////////////////////////////////////////////////////////////
        //void Sleep( unsigned long timems );
        //  Puts the calling thread to sleep for the specified miliseconds
        //
        //Parameter(s)
        //  unsigned long timemes  -  time interval to put the thread to sleep for
        //
        //Return Value
        //  None
        //
        //
        /////////////////////////////////////////////////////////////////////////
        void Sleep(unsigned long timems);
    }


inline uint32 getMSTime()
    {
        uint32 MSTime = 0;
#ifdef WIN32
        MSTime = GetTickCount();
#else
        timeval tv;
        gettimeofday(&tv, NULL);
        MSTime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
        return MSTime;
    }

#endif
