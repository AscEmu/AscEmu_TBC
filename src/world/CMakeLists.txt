# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

# set up our project name
project(world)

file(GLOB_RECURSE sources_BufferPools BufferPools/*.cpp BufferPools/*.h)
file(GLOB_RECURSE sources_DBC DBC/*.cpp DBC/*.h DBC/*.hpp)
file(GLOB_RECURSE sources_MapManagement MapManagement/*.cpp MapManagement/*.hpp)
file(GLOB_RECURSE sources_MapMgAreaMananagement MapManagement/AreaMananagement/*.cpp MapManagement/AreaMananagement/*.hpp)
file(GLOB sources_localdir *.cpp *.h *.hpp)

set(prefix ${ROOT_PATH}/src/world)
set(ascemu_world_SRCS
  ${ascemu_world_SRCS} 
  ${sources_BufferPools}
  ${sources_DBC}
  ${sources_MapManagement}
  ${sources_MapMgAreaMananagement}
  ${sources_localdir}
)

include(PCHSupport)
include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${ROOT_PATH}/src/shared
   ${DEPENDENCY_ROOT}/zlib
   ${DEPENDENCY_ROOT}/openssl
   ${DEPENDENCY_ROOT}/pcre/include
   ${RECASTNAVIGATION}/Detour/Include
   ${DEPENDENCY_ROOT}/vmaplib/include
   ${DEPENDENCY_ROOT}/g3dlite/include
   )

link_directories( ${DEPENDENCY_LIBS} ${EXTRA_LIBS_PATH} )

set(WIN_RESOURCE_FILE ${ROOT_PATH}/src/world/resources.rc)

add_executable(${PROJECT_NAME} ${ascemu_world_SRCS} ${WIN_RESOURCE_FILE})

if(CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} StdAfx.h ${prefix}/StdAfx.cpp)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)

add_dependencies( ${PROJECT_NAME} shared g3dlite vmaplib Detour Recast)
target_link_libraries( ${PROJECT_NAME} shared  g3dlite vmaplib Detour Recast ${PCRE_LIBRARIES})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
