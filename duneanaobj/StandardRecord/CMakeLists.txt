add_subdirectory(Proxy)
add_subdirectory(Flat)

# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

add_library(duneanaobj_StandardRecord
            ${src_files})
          target_include_directories(duneanaobj_StandardRecord ${SRPROXY_DIR})
target_link_libraries(duneanaobj_StandardRecord
                 ROOT::Core ROOT::Physics )

# n.b.: missing the dictionary and installation!
