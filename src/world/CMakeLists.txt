# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

# set up our project name
project(world)

file(GLOB_RECURSE sources_BufferPools BufferPools/*.cpp BufferPools/*.h)
file(GLOB_RECURSE sources_Commands Commands/*.cpp)
file(GLOB_RECURSE sources_DBC DBC/*.cpp DBC/*.h DBC/*.hpp)
file(GLOB_RECURSE sources_MapManagement MapManagement/*.cpp MapManagement/*.hpp)
file(GLOB_RECURSE sources_MapMgAreaMananagement MapManagement/AreaMananagement/*.cpp MapManagement/AreaMananagement/*.hpp)
file(GLOB sources_localdir *.cpp *.h *.hpp)

set(ascemu_world_SRCS
  ${ascemu_world_SRCS} 
  ${sources_BufferPools}
  ${sources_Commands}
  ${sources_DBC}
  ${sources_MapManagement}
  ${sources_MapMgAreaMananagement}
  ${sources_localdir}
)

include_directories(
   ${OPENSSL_INCLUDE_DIR}
   ${PCRE_INCLUDE_DIR}
   ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include
   ${CMAKE_SOURCE_DIR}/dep/vmaplib/include
   ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
   ${CMAKE_SOURCE_DIR}/src/shared
   ${ZLIB_INCLUDE_DIRS}
   ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${PROJECT_NAME} STATIC ${ascemu_world_SRCS})
if(USE_PCH AND PCHSupport_FOUND)
    ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} StdAfx.h ${CMAKE_CURRENT_SOURCE_DIR}/StdAfx.cpp)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/WorldConf.h.in ${CMAKE_CURRENT_SOURCE_DIR}/WorldConf.h)

target_link_libraries( ${PROJECT_NAME} shared g3dlite vmaplib Detour Recast ${PCRE_LIBRARIES})
