add_subdirectory(Proxy)
add_subdirectory(Flat)

# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} "$ENV{ROOT_INCLUDE_PATH}")

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )
FILE( GLOB inc_files *.h )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

if(DEFINED CETMODULES_CURRENT_PROJECT_NAME)
  cet_make_library( LIBRARY_NAME duneanaobj_StandardRecord
                    SOURCE       ${src_files}
                    LIBRARIES    ROOT::Core ROOT::Physics
                  )

  build_dictionary( duneanaobj_StandardRecord
                    DICTIONARY_LIBRARIES duneanaobj_StandardRecord
                  )

  install_headers()
  install_source()
else()
  add_library(duneanaobj_StandardRecord SHARED ${src_files})
  target_link_libraries(duneanaobj_StandardRecord PUBLIC ROOT::Core ROOT::Physics)

  #ROOT_GENERATE_DICTIONARY(duneanaobj_StandardRecord_dict DICTIONARY_LIBRARIES duneanaobj_StandardRecord)
  # TODO: Need to generate the dictionary

  install(TARGETS duneanaobj_StandardRecord)
  install(FILES ${inc_files} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/duneanaobj/StandardRecord)
  install(EXPORT duneanaobjTargets NAMESPACE duneanaobj:: DESTINATION lib/cmake/duneanaobj)
endif()
