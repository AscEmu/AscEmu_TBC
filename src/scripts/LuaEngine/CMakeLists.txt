if(NOT BUILD_LUAENGINE )
  message("\tLuaEngine was skipped because BUILD_LUAENGINE is unchecked.")
  return()
endif()

############## lualib
PROJECT(lualib C)

#SRCS - contains the source files that compose this project.
file(GLOB_RECURSE sources_Lua lua/*.c lua/*.h)

set(ascemu_lualib_SRCS
  ${ascemu_lualib_SRCS}
  ${sources_Lua}
)

ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS)
IF( NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
	ADD_DEFINITIONS( -DLUA_USE_APICHECK )
ENDIF()
ADD_LIBRARY( ${PROJECT_NAME} STATIC ${ascemu_lualib_SRCS} )
REMOVE_DEFINITIONS( -std=c++0x )
IF( IS_64BIT )
	SET_PROPERTY( TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_FLAGS "-fPIC")
ENDIF()

############## luaengine

project(LuaEngine)

#SRCS - contains the source files that compose this project.
file(GLOB sources_localdir *.cpp *.h)

set(ascemu_luaengine_SRCS
  ${ascemu_luaengine_SRCS}
  ${sources_localdir}
  #${sources_Lua}
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

