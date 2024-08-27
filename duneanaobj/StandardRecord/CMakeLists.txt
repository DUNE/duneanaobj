add_subdirectory(Proxy)
add_subdirectory(Flat)

# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} "$ENV{ROOT_INCLUDE_PATH}")

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

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
    add_library(duneanaobj_StandardRecord
                ${src_files})
    target_link_libraries(duneanaobj_StandardRecord
                     ROOT::Core ROOT::Physics )

    # n.b.: missing the dictionary and installation!
endif()
