if(NOT BUILD_QUESTSCRIPTS)
  message("\tQuestScripts was skipped because BUILD_QUESTSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_QUESTSCRIPTS)

PROJECT(QuestScripts)

file(GLOB_RECURSE sources_EAS EAS/*.cpp EAS/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(ascemu_questscripts_SRCS
  ${ascemu_questscripts_SRCS}
  ${sources_localdir}
  ${sources_EAS}
)

include_directories( ${GLOBAL_INCLUDE_DIRS} ${ascemu_questscripts_SRCS} ${DEPENDENCY_ROOT}/zlib )

add_library( ${PROJECT_NAME} SHARED ${ascemu_questscripts_SRCS} )

#common include directories that script libraries might include.
SET( include_dirs ${GLOBAL_INCLUDE_DIRS} )

add_dependencies( ${PROJECT_NAME} shared world QuestScripts )
add_definitions( -DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING )
target_link_libraries( ${PROJECT_NAME} world )

include(PCHSupport)
IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${ascemu_questscripts_SRCS}/Setup.cpp)
ENDIF()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})
