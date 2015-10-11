# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

if(NOT BUILD_QUESTSCRIPTS )
  message("\tQuestScripts was skipped because BUILD_QUESTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_QUESTSCRIPTS)

# set up our project name
project(QuestScripts)

set(prefix ${SCRIPTS_PATH}/${PROJECT_NAME})

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

foreach(src IN ITEMS ${sources})
   set(SRCS ${SRCS} ${prefix}/${src})
endforeach(src)
foreach(src IN ITEMS ${headers})
   set(HEADERS ${HEADERS} ${prefix}/${src})
endforeach(src)

include_directories( ${include_dirs} ${prefix} ${DEPENDENCY_ROOT}/zlib)
add_library(${PROJECT_NAME} SHARED ${SRCS} ${HEADERS})
add_dependencies(${PROJECT_NAME} ${script_dependencies})
target_link_libraries(${PROJECT_NAME} ${script_linkages})

include(PCHSupport)
if(CMAKE_GENERATOR MATCHES Visual*)
   ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})
