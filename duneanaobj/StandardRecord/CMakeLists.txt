add_subdirectory(Proxy)
add_subdirectory(Flat)

# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.22.02) - avoid directory-scope functions: use target_link_libraries() with target semantics or target_include_directories() whenever possible

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

cet_make_library( LIBRARY_NAME duneanaobj_StandardRecord
                  SOURCE       ${src_files}
                  LIBRARIES    ROOT::Core ROOT::Physics
                )

build_dictionary( duneanaobj_StandardRecord
                  DICTIONARY_LIBRARIES duneanaobj_StandardRecord
                )

install_headers()
install_source()
