# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

#set our projectname
project(SpellHandlers)

set(prefix ${ROOT_PATH}/src/scripts/${PROJECT_NAME})

#sources -contains source files for our library.
set(sources
   HunterSpells.cpp
   ItemSpells_1.cpp
   MageSpells.cpp
   PaladinSpells.cpp
   RogueSpells.cpp
   Setup.cpp
   ShamanSpells.cpp
   WarlockSpells.cpp
   WarriorSpells.cpp
   )

foreach(src IN ITEMS ${sources})
   set(SRCS ${SRCS} ${prefix}/${src})
endforeach(src)

include_directories(${GLOBAL_INCLUDE_DIRS} ${DEPENDENCY_ROOT}/zlib)
add_library(${PROJECT_NAME} SHARED ${SRCS})
add_dependencies(${PROJECT_NAME} ${script_dependencies})
add_definitions(-DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING)
target_link_libraries(${PROJECT_NAME} ${script_linkages})

include(PCHSupport)
if(CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH} )
