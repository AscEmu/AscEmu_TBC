# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

if(NOT BUILD_QUESTSCRIPTS )
  message("\tQuestScripts was skipped because BUILD_QUESTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_QUESTSCRIPTS)

# set up our project name
project(QuestScripts)

SET(sources
   Azuremyst_Isle.cpp
   BladeEdge_Mountains.cpp
   Druid.cpp
   Eastern_Plaguelands.cpp
   Hellfire_Peninsula.cpp
   Isle_of_QuelDanas.cpp
   Mage.cpp
   Nagrand.cpp
   Paladin.cpp
   Shadowmoon.cpp
   Silverpine_Forest.cpp
   Terrokar_Forest.cpp
   The_Barrens.cpp
   Undercity.cpp
   Ungoro.cpp
   Zangarmarsh.cpp
   Setup.cpp 
   )

set(headers
   Setup.h
   EAS/EasyFunctions.h
   )

include_directories(
   ${OPENSSL_INCLUDE_DIR}
   ${PCRE_INCLUDE_DIR}
   ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour/Include
   ${CMAKE_SOURCE_DIR}/dep/vmaplib/include
   ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
   ${CMAKE_SOURCE_DIR}/src/shared
   ${CMAKE_SOURCE_DIR}/src/world
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${ZLIB_INCLUDE_DIRS}
)
add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

target_link_libraries(${PROJECT_NAME} world)

if(USE_PCH AND PCHSupport_FOUND)
    ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${CMAKE_CURRENT_SOURCE_DIR}/Setup.cpp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})
unset(sources)
unset(headers)
