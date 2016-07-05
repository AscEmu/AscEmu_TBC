# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

#set our projectname
project(SpellHandlers)

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
   MiscSpells.cpp
   )

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})
add_definitions(-DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING)

# special case for project linking
# on some operating systems linking is a bit strange
# OS X can't link executable, MSVC can't link world library... weird
if(WIN32)
    add_dependencies(${PROJECT_NAME} worldserver)
    target_link_libraries(${PROJECT_NAME} worldserver)
elseif(APPLE)
    add_dependencies(${PROJECT_NAME} world)
    target_link_libraries(${PROJECT_NAME} world)
endif()
if(USE_PCH AND PCHSupport_FOUND)
    ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${CMAKE_CURRENT_SOURCE_DIR}/Setup.cpp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH} )

unset(sources)
unset(headers)
