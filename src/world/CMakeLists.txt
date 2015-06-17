PROJECT(arcemu-world)

file(GLOB_RECURSE sources_BufferPools BufferPools/*.cpp BufferPools/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(arcemu_world_SRCS
  ${arcemu_world_SRCS} 
  ${sources_BufferPools}
  ${sources_localdir}
)

include(PCHSupport)
include_directories( ${GLOBAL_INCLUDE_DIRS} )
link_directories( ${DEPENDENCY_LIBS} ${EXTRA_LIBS_PATH} )

SET(WIN_RESOURCE_FILE ${ROOT_PATH}/src/world/resources.rc)

ADD_EXECUTABLE( ${PROJECT_NAME} ${arcemu_world_SRCS} ${WIN_RESOURCE_FILE} )

IF( CMAKE_GENERATOR MATCHES Visual*)
	ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} StdAfx.h ${sources_localdir}/StdAfx.cpp)
ENDIF()
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)

add_dependencies( ${PROJECT_NAME} arcemu-shared g3dlite vmaplib detour recast )
target_link_libraries( ${PROJECT_NAME} arcemu-shared g3dlite vmaplib detour recast ${PCRE_LIBRARIES} )
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)





