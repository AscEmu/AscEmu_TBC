if(NOT BUILD_CUSTOMSCRIPTS)
  message("\tCustomScripts was skipped because BUILD_CUSTOMSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_CUSTOMSCRIPTS)

PROJECT(CustomScripts)

file(GLOB sources_localdir *.cpp *.h)

set(ascemu_customscripts_SRCS
  ${ascemu_customscripts_SRCS}
  ${sources_localdir}
)

include_directories( ${GLOBAL_INCLUDE_DIRS} ${ascemu_customscripts_SRCS} )

add_library( ${PROJECT_NAME} SHARED ${ascemu_customscripts_SRCS} )

#common include directories that script libraries might include.
SET( include_dirs ${GLOBAL_INCLUDE_DIRS} )

add_dependencies( ${PROJECT_NAME} shared world )
add_definitions( -DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING )
target_link_libraries( ${PROJECT_NAME} world )

include(PCHSupport)
IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${sources_localdir}/Setup.cpp)
ENDIF()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})
