#child CMakeLists use this variable to access the source file directories. 
#e.g ${SCRIPTS_PATH}/LuaEngine to access the source files for LuaEngine.

if( NOT BUILD_ASCEMUSCRIPTS )
  message( WARNING, "BUILD_ASCEMUSCRIPTS option is set to false. Script libraries will not be built." )
  return()
endif(NOT BUILD_ASCEMUSCRIPTS)
message("Configuring scripts :")
SET( SCRIPTS_PATH ${ROOT_PATH}/src/scripts )

#common include directories that script libraries might include.
SET( include_dirs ${GLOBAL_INCLUDE_DIRS} )

#All script libraries have SCRIPTLIB defined.
add_definitions(-DSCRIPTLIB -DSKIP_ALLOCATOR_SHARING)
SET( BUILD_CUSTOMSCRIPTS FALSE CACHE BOOL "Build ascCustomScripts.")
SET( BUILD_EVENTSCRIPTS FALSE CACHE BOOL "Build ascEventScripts.")
SET( BUILD_INSTANCESCRIPTS TRUE CACHE BOOL "Build ascInstanceScripts.")
SET( BUILD_EXTRASCRIPTS TRUE CACHE BOOL "Build ascExtraScripts.")
SET( BUILD_GOSSIPSCRIPTS TRUE CACHE BOOL "Build ascGossipScripts.")
SET( BUILD_QUESTSCRIPTS TRUE CACHE BOOL "Build ascQuestScripts.")
SET( BUILD_MISCSCRIPTS TRUE CACHE BOOL "Build ascMiscScripts." )
set( BUILD_LUAENGINE TRUE CACHE BOOL "Build LuaEngine." )

add_subdirectory( CustomScripts )
add_subdirectory( EventScripts )
add_subdirectory( InstanceScripts )
add_subdirectory( ExtraScripts )
add_subdirectory( GossipScripts )
add_subdirectory( QuestScripts )
add_subdirectory( LuaEngine )
add_subdirectory( LuaEngine/lua )
add_subdirectory( MiscScripts )

unset(SCRIPTS_PATH)
unset(include_dirs)