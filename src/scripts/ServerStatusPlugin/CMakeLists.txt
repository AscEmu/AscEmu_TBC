if(NOT BUILD_SERVERSTATUSPLUGIN)
  message("\tServerStatusPlugin was skipped because BUILD_SERVERSTATUSPLUGINS is unchecked.")
  return()
endif(NOT BUILD_SERVERSTATUSPLUGIN)

PROJECT(ServerStatusPlugin)

file(GLOB sources_localdir *.cpp *.h)

set(ascemu_serverstatusplugin_SRCS
  ${ascemu_serverstatusplugin_SRCS}
  ${sources_localdir}
)

include_directories( ${GLOBAL_INCLUDE_DIRS} ${ascemu_serverstatusplugin_SRCS} )

add_library( ${PROJECT_NAME} SHARED ${ascemu_serverstatusplugin_SRCS} )

#common include directories that script libraries might include.
SET( include_dirs ${GLOBAL_INCLUDE_DIRS} )

add_dependencies( ${PROJECT_NAME} shared world )
add_definitions( -DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING )
target_link_libraries( ${PROJECT_NAME} world )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})
