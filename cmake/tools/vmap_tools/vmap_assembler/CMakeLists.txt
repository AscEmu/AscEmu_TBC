PROJECT(vmap_assembler CXX)
SET( prefix ${ROOT_PATH}/src/tools/vmap_tools/vmap_assembler)
SET( sources
vmap_assembler.cpp
)

foreach(src IN ITEMS ${sources} )
  SET( SRCS ${SRCS} ${prefix}/${src} )
endforeach(src)

include_directories(
   ${DEPENDENCY_INCLUDE_ROOT}/vmaplib
   ${DEPENDENCY_INCLUDE_ROOT}/g3dlite
   ${ZLIB_LIBRARIES}
   )

ADD_EXECUTABLE( ${PROJECT_NAME} ${SRCS} )

if(APPLE)
	set_target_properties(vmap4assembler PROPERTIES LINK_FLAGS "-framework Carbon")
endif()

target_link_libraries( ${PROJECT_NAME} vmaplib g3dlite ${ZLIB_LIBRARIES} )


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${ASCEMU_TOOLS_PATH} )
