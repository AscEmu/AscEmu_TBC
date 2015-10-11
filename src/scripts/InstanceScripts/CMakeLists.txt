# Copyright (C) 2014-2015 AscEmu Team <http://www.ascemu.org>

if(NOT BUILD_INSTANCESCRIPTS )
  message("\tInstanceScripts was skipped because BUILD_INSTANCESCRIPTS is unchecked.")
  return()
endif(NOT BUILD_INSTANCESCRIPTS)

# set up our project name
project(InstanceScripts)

set(prefix ${SCRIPTS_PATH}/InstanceScripts)

#sources -contains source files for our library.
set(sources
    Instance_Arcatraz.cpp 
    Instance_AuchenaiCrypts.cpp 
    Instance_BlackMorass.cpp 
    Instance_BlackrockDepths.cpp 
    Instance_BlackrockSpire.cpp 
    Instance_BloodFurnace.cpp 
    Instance_Botanica.cpp 
    Instance_Deadmines.cpp 
    Instance_DireMaul.cpp 
    Instance_HellfireRamparts.cpp 
    Instance_MagistersTerrace.cpp 
    Instance_ManaTombs.cpp 
    Instance_Maraudon.cpp 
    Instance_OldHillsbradFoothills.cpp 
    Instance_RagefireChasm.cpp 
    Instance_RazorfenDowns.cpp 
    Instance_ScarletMonastery.cpp 
    Instance_Scholomance.cpp 
    Instance_SethekkHalls.cpp 
    Instance_ShadowLabyrinth.cpp 
    Instance_ShadowfangKeep.cpp 
    Instance_TheMechanar.cpp 
    Instance_TheShatteredHalls.cpp 
    Instance_TheSlavePens.cpp 
    Instance_TheSteamvault.cpp 
    Instance_TheStockade.cpp
    Instance_TheUnderbog.cpp 
    Instance_Uldaman.cpp 	
    Instance_WailingCaverns.cpp 
    Instance_ZulFarrak.cpp 
    Raid_BlackTemple.cpp 
    Raid_BlackwingLair.cpp 
    Raid_CoT_BattleOfMountHyjal.cpp 
    Raid_GruulsLair.cpp
    Raid_Karazhan.cpp 
    Raid_Magtheridons_Lair.cpp 
    Raid_MoltenCore.cpp 
    Raid_Naxxramas.cpp 
    Raid_OnyxiasLair.cpp 
    Raid_SerpentshrineCavern.cpp
    Raid_SunwellPlateau.cpp  
    Raid_TheEye.cpp  
    Raid_WorldBosses.cpp 
    Raid_ZulAman.cpp
    Event_DarkPortal.cpp
    GenericAI.cpp 
    Base.cpp 
    Setup.cpp
    )

set(headers
    Setup.h
    Base.h
    )

foreach(src IN ITEMS ${sources})
   set(SRCS ${SRCS} ${prefix}/${src})
endforeach(src)
foreach(src IN ITEMS ${headers})
   set(HEADERS ${HEADERS} ${prefix}/${src})
endforeach(src)

include_directories(${include_dirs} ${prefix} ${DEPENDENCY_ROOT}/zlib)
add_library(${PROJECT_NAME} SHARED ${SRCS} ${HEADERS})
add_dependencies(${PROJECT_NAME} ${script_dependencies})
target_link_libraries(${PROJECT_NAME} ${script_linkages})

include(PCHSupport)
if(CMAKE_GENERATOR MATCHES Visual*)
   ADD_NATIVE_PRECOMPILED_HEADER(${PROJECT_NAME} Setup.h ${prefix}/Setup.cpp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_SCRIPTLIB_PATH} LIBRARY DESTINATION ${ASCEMU_SCRIPTLIB_PATH})
