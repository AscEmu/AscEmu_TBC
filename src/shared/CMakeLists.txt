# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

# set up our project name
project(shared)
set(prefix ${ROOT_PATH}/src/shared)
set(sources
   Auth/BigNumber.cpp
   Auth/MD5.cpp
   Auth/Sha1.cpp
   Auth/WowCrypt.cpp
   Config/Config.cpp
   Database/CreateInterface.cpp
   Database/Database.cpp
   Database/DBC.cpp
   Database/dbcfile.cpp
   Database/DBCStores.cpp
   Database/MySQLDatabase.cpp
   Database/PostgresDatabase.cpp
   Database/SQLiteDatabase.cpp
   Network/CircularBuffer.cpp
   Network/Socket.cpp
   Threading/AtomicBoolean.cpp
   Threading/AtomicCounter.cpp
   Threading/AtomicFloat.cpp
   Threading/AtomicULong.cpp
   Threading/ConditionVariable.cpp
   Threading/Mutex.cpp
   Threading/ThreadPool.cpp
   arcemu_getopt.cpp
   CoreMemoryAllocator.cpp
   CoreMemoryAllocator_Core.cpp
   CrashHandler.cpp
   crc32.cpp
   CThreads.cpp
   DynLib.cpp
   FindFiles.cpp
   Log.cpp
   MemoryLeaks.cpp
   MersenneTwister.cpp
   PacketLog.cpp
   Util.cpp
	)

set(headers
   Auth/BigNumber.h
   Auth/MD5.h
   Auth/Sha1.h
   Auth/WowCrypt.h
   Config/Config.h
   Config/ConfigEnv.h
   Database/Database.h
   Database/DatabaseEnv.h
   Database/DataStore.h
   Database/DBC.h
   Database/dbcfile.h
   Database/DBCStores.h
   Database/Field.h
   Database/MySQLDatabase.h
   Database/PostgresDatabase.h
   Database/SQLiteDatabase.h
   mysql/mysql.h
   Network/CircularBuffer.h
   Network/ListenSocketLinux.h
   Network/ListenSocketWin32.h
   Network/Network.h
   Network/Socket.h
   Network/SocketDefines.h
   Network/SocketMgrLinux.h
   Network/SocketMgrWin32.h
   Network/SocketOps.h
   Threading/AtomicBoolean.h
   Threading/AtomicCounter.h
   Threading/AtomicFloat.h
   Threading/AtomicULong.h
   Threading/Condition.h
   Threading/ConditionVariable.h
   Threading/Guard.h
   Threading/LockedQueue.h
   Threading/Mutex.h
   Threading/Queue.h
   Threading/RWLock.h
   Threading/Threading.h
   Threading/ThreadPool.h
   Threading/ThreadStarter.h
   arcemu_getopt.h
   arcemuConfig.h
   AuthCodes.h
   ByteBuffer.h
   CallBack.h
   CircularQueue.h
   Common.h
   CrashHandler.h
   crc32.h
   CThreads.h
   DynLib.hpp
   Errors.h
   FastQueue.h
   FindFiles.hpp
   FindFilesResult.hpp
   git_version.h
   LocationVector.h
   Log.h
   MemoryLeaks.h
   MersenneTwister.h
   New-Bytebuffer.h
   NGLog.h
   PacketLog.h
   PreallocatedQueue.h
   RC4Engine.h
   RealmPacket.h
   Singleton.h
   SmartPointer.h
   StackBuffer.h
   StackWalker.h
   Storage.h
   Timer.h
   Util.h
   WorldPacket.h
   WoWGuid.h
	)

if(WIN32)
   set(sources ${sources} Network/SocketMgrWin32.cpp Network/SocketOpsWin32.cpp Network/SocketWin32.cpp StackWalker.cpp)
else(WIN32)
   set(sources ${sources} Network/SocketMgrLinux.cpp Network/SocketLinux.cpp Network/SocketOpsLinux.cpp)
endif(WIN32)

foreach(src IN ITEMS ${sources})
   set(SRCS ${SRCS} ${prefix}/${src})
endforeach(src)
foreach(src IN ITEMS ${headers})
   set(HEADERS ${HEADERS} ${prefix}/${src})
endforeach(src)

include_directories( ${GLOBAL_INCLUDE_DIRS} )

if(IS_64BIT)
   link_directories(${DEPENDENCY_DLLS64})
else()
	link_directories(${DEPENDENCY_DLLS})
endif()
link_directories(${DEPENDENCY_LIBS})

add_library(${PROJECT_NAME} STATIC ${SRCS} ${HEADERS})
target_link_libraries( ${PROJECT_NAME} ${ZLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${MYSQL_LIBRARY} ${OPENSSL_LIBRARIES} ${EXTRA_LIBS} )
