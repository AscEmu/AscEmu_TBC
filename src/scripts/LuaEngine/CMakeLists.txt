if(NOT BUILD_LUAENGINE )
  message("\tLuaEngine was skipped because BUILD_LUAENGINE is unchecked.")
  return()
endif()


project(LuaEngine)

#SRCS - contains the source files that compose this project.
file(GLOB sources_localdir *.cpp *.h)

set(ascemu_luaengine_SRCS
  ${ascemu_luaengine_SRCS}
  ${sources_localdir}
)

include_directories( ${include_dirs} ${ascemu_luaengine_SRCS} ${GLOBAL_INCLUDE_DIRS} )
add_definitions( -DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING )
IF( IS_LINUX )
	add_definitions(-Wno-deprecated)
ENDIF()


add_library(${PROJECT_NAME} SHARED ${ascemu_luaengine_SRCS})
add_dependencies( ${PROJECT_NAME} lualib shared world)
target_link_libraries( ${PROJECT_NAME} lualib world)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})

