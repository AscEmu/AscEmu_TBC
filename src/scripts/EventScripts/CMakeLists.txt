# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

if(NOT BUILD_EVENTSCRIPTS)
  message("\tEventScripts was skipped because BUILD_EVENTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_EVENTSCRIPTS)

project(EventScripts)

file(GLOB sources_localdir *.cpp *.h)

set(ascemu_eventscripts_SRCS
  ${ascemu_eventscripts_SRCS}
  ${sources_localdir}
)

add_library(${PROJECT_NAME} SHARED ${ascemu_eventscripts_SRCS})
add_dependencies(${PROJECT_NAME} ${script_dependencies})
target_link_libraries(${PROJECT_NAME} ${ascemu_eventscripts_SRCS})

include(PCHSupport)
if(CMAKE_GENERATOR MATCHES Visual*)
   ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH} )
