if(NOT BUILD_ASCEMUSCRIPTS)
  message("\tAscEmuScripts was skipped because BUILD_ASCEMUSCRIPTS is unchecked.")
  return()
endif(NOT BUILD_ASCEMUSCRIPTS)

PROJECT(scripts)

file(GLOB_RECURSE sources_Base Base/*.cpp Base/*.h)
file(GLOB_RECURSE sources_BaseEAS Base/EAS/*.cpp Base/EAS/*.h)
file(GLOB_RECURSE sources_CustomScripts CustomScripts/*.cpp CustomScripts/*.h)
file(GLOB_RECURSE sources_ExtraScripts ExtraScripts/*.cpp ExtraScripts/*.h)
file(GLOB_RECURSE sources_GossipScripts GossipScripts/*.cpp GossipScripts/*.h)
file(GLOB_RECURSE sources_InstanceScripts InstanceScripts/*.cpp InstanceScripts/*.h)
file(GLOB_RECURSE sources_MiscScripts MiscScripts/*.cpp MiscScripts/*.h)
file(GLOB_RECURSE sources_QuestScripts QuestScripts/*.cpp QuestScripts/*.h)
file(GLOB_RECURSE sources_ServerStatusPlugin ServerStatusPlugin/*.cpp ServerStatusPlugin/*.h)
file(GLOB_RECURSE sources_SpellHandlers SpellHandlers/*.cpp SpellHandlers/*.h)
file(GLOB_RECURSE sources_WorldPvpScripts WorldPvpScripts/*.cpp WorldPvpScripts/*.h)
file(GLOB sources_localdir *.cpp *.h)

set(ascemu_scripts_SRCS
  ${ascemu_scripts_SRCS}
  ${sources_localdir}
  ${sources_Base}
  ${sources_BaseEAS}
  ${sources_CustomScripts}
  ${sources_ExtraScripts}
  ${sources_GossipScripts}
  ${sources_InstanceScripts}
  ${sources_MiscScripts}
  ${sources_QuestScripts}
  ${sources_ServerStatusPlugin}
  ${sources_SpellHandlers}
  ${sources_WorldPvpScripts}
)

include_directories( ${GLOBAL_INCLUDE_DIRS} ${ascemu_scripts_SRCS} )

add_library( ${PROJECT_NAME} SHARED ${ascemu_scripts_SRCS} )

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
