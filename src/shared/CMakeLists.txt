PROJECT(arcemu-shared)

file(GLOB_RECURSE sources_Auth Auth/*.cpp Auth/*.h)
file(GLOB_RECURSE sources_Config Config/*.cpp Config/*.h)
file(GLOB_RECURSE sources_Database Database/*.cpp Database/*.h)
file(GLOB_RECURSE sources_Network Network/*.cpp Network/*.h)
file(GLOB_RECURSE sources_Threading Threading/*.cpp Threading/*.h)
file(GLOB sources_localdir *.cpp *.h *.hpp)

set(arcemu_shared_SRCS
  ${arcemu_shared_SRCS}
  ${sources_localdir}
  ${sources_Auth}
  ${sources_Config}
  ${sources_Database}
  ${sources_Network}
  ${sources_Threading}
)

include_directories( ${GLOBAL_INCLUDE_DIRS} )
IF( IS_64BIT )
	link_directories( ${DEPENDENCY_DLLS64} )
ELSE()
	link_directories( ${DEPENDENCY_DLLS} )
ENDIF()
link_directories( ${DEPENDENCY_LIBS} )

ADD_LIBRARY( ${PROJECT_NAME} STATIC ${arcemu_shared_SRCS} )

target_link_libraries( ${PROJECT_NAME} ${ZLIB_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${MYSQL_LIBRARY} ${OPENSSL_LIBRARIES} ${EXTRA_LIBS} )

