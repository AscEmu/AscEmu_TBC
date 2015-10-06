############## lualib
PROJECT(lualib C)

#SRCS - contains the source files that compose this project.
file(GLOB_RECURSE sources_Lua *.c *.h)

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