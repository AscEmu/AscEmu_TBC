# Copyright (C) 2014-2016 AscEmu Team <http://www.ascemu.org>

# set up our project name
project(shared)

set(sources
   Auth/BigNumber.cpp
   Auth/MD5.cpp
   Auth/Sha1.cpp
   Auth/WowCrypt.cpp
   Config/Config.cpp
   Database/CreateInterface.cpp
   Database/Database.cpp
   Database/dbcfile.cpp
   Database/MySQLDatabase.cpp
   Network/CircularBuffer.cpp
   Network/Socket.cpp
   Threading/AtomicBoolean.cpp
   Threading/AtomicCounter.cpp
   Threading/AtomicFloat.cpp
   Threading/AtomicULong.cpp
   Threading/ConditionVariable.cpp
   Threading/Mutex.cpp
   Threading/ThreadPool.cpp
   ascemu_getopt.cpp
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
   PerformanceCounter.cpp
   SysInfo.cpp
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
   Database/dbcfile.h
   Database/Field.h
   Database/MySQLDatabase.h
   Network/CircularBuffer.h
   Network/ListenSocketLinux.h
   Network/ListenSocketWin32.h
   Network/Network.h
   Network/NetworkIncludes.hpp
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
   ascemu_getopt.h
   ascemuConfig.h
   AuthCodes.h
   ByteBuffer.h
   CallBack.h
   CircularQueue.h
   Common.h
   CommonDefines.hpp
   CommonHelpers.hpp
   CommonTypes.hpp
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
   PacketLog.h
   PerformanceCounter.hpp
   PreallocatedQueue.h
   RC4Engine.h
   RealmPacket.h
   Singleton.h
   SmartPointer.h
   StackBuffer.h
   StackWalker.h
   Storage.h
   SysInfo.hpp
   Util.h
   WorldPacket.h
   WoWGuid.h
	)

if(WIN32)
   set(sources ${sources} Network/SocketMgrWin32.cpp Network/SocketOpsWin32.cpp Network/SocketWin32.cpp StackWalker.cpp)
else(WIN32)
   set(sources ${sources} Network/SocketMgrLinux.cpp Network/SocketLinux.cpp Network/SocketOpsLinux.cpp)
endif(WIN32)

include_directories(
    ${OPENSSL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIRS}
    ${MYSQL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${MYSQL_LIBRARIES} ${OPENSSL_LIBRARIES} ${EXTRA_LIBS})

unset(sources)
unset(headers)
