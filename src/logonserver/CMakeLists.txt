PROJECT(logon)

file(GLOB sources_localdir *.cpp *.h)

set(arcemu_logon_SRCS
  ${arcemu_logon_SRCS} 
  ${sources_localdir}
)

include_directories(
   ${GLOBAL_INCLUDE_DIRS}
   ${CMAKE_CURRENT_SOURCE_DIR}
   )
link_directories( ${EXTRA_LIBS_PATH} ${DEPENDENCY_LIBS} )
IF( IS_64BIT )
	link_directories( ${DEPENDENCY_DLLS64} )
ENDIF()

include(PCHSupport)

SET(WIN_RESOURCE_FILE ${ROOT_PATH}/src/logonserver/resources.rc)
ADD_EXECUTABLE( ${PROJECT_NAME} ${arcemu_logon_SRCS} ${WIN_RESOURCE_FILE} )

IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} LogonStdAfx.h ${sources_localdir}/LogonStdAfx.cpp)
ENDIF()
#Link our shared lib.
target_link_libraries( ${PROJECT_NAME} shared ${ZLIB_LIBRARIES} ${PCRE_LIBRARIES} )
#Provide make install rules.
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

