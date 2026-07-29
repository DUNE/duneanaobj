
# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

# Locate the SRProxy code generator and runtime headers once, here, so both the
# Proxy/ and Flat/ subdirectories share the result. Prefer a find_package()'able
# SRProxy (which exports the SRProxy::SRProxy target carrying its headers), and
# cascade back to the older $SRPROXY_INC / $SRPROXY_DIR layout otherwise.
find_package(SRProxy QUIET CONFIG)
if(SRProxy_FOUND)
    message(STATUS "Found SRProxy CMake package at ${SRProxy_DIR}")
    # SRProxy exports its headers but not the gen_srproxy executable,
    # so look for it under the package's install prefix (then fall back to $SRPROXY_DIR/bin).
    get_filename_component(SRPROXY_PREFIX "${SRProxy_DIR}/../../.." ABSOLUTE)
    find_program(GEN_SRPROXY gen_srproxy HINTS "${SRPROXY_PREFIX}/bin" $ENV{SRPROXY_DIR}/bin)
    get_target_property(SRPROXY_INCLUDE_DIRS SRProxy::SRProxy INTERFACE_INCLUDE_DIRECTORIES)
    include_directories(${SRPROXY_INCLUDE_DIRS})
else()
    message(STATUS "SRProxy CMake package not found; using $SRPROXY_INC / $SRPROXY_DIR")
    find_program(GEN_SRPROXY gen_srproxy HINTS $ENV{SRPROXY_DIR}/bin)
    include_directories($ENV{SRPROXY_INC})
endif()

# Proxy/ and Flat/ generate their sources with gen_srproxy, so only descend into
# them when it was found.
if(GEN_SRPROXY)
    add_subdirectory(Proxy)
    add_subdirectory(Flat)
else()
    message(WARNING "Could not find gen_srproxy; skipping the Proxy and Flat subdirectories")
endif()

if(NOT SKIP_CET)
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
    # n.b.: missing Proxy, Plain and the dictionary!

    include(GNUInstallDirs)

    # Create and configure library target
    add_library( StandardRecord SHARED
                 ${src_files}
               )

    target_link_libraries( StandardRecord
                           ROOT::Core ROOT::Physics
                         )
    target_include_directories(StandardRecord INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
            ${ROOT_INCLUDE_DIRS}
    )
    # Setup installation
    file( GLOB headers_files *.h )
    set_target_properties(StandardRecord PROPERTIES PUBLIC_HEADER "${headers_files}")

    install( TARGETS StandardRecord EXPORT duneanaobjTargets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION include/)
#    install( FILES ${headers_files} DESTINATION "include/duneanaobj/StandardRecord" )

    # ROOT I/O dictionary. The CET path gets this from cet's build_dictionary;
    # here we drive rootcling directly via ROOT's root_generate_dictionary,
    # fed the same classes.h / classes_def.xml selection file. The result is a
    # standalone StandardRecord_dict library (exported as
    # duneanaobj::StandardRecord_dict) plus the .rootmap and _rdict.pcm that
    # ROOT needs for autoloading at runtime.
    root_generate_dictionary( G__StandardRecord
                              ${CMAKE_CURRENT_SOURCE_DIR}/classes.h
                              MODULE StandardRecord_dict
                              LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/classes_def.xml
                            )

    add_library( StandardRecord_dict SHARED G__StandardRecord.cxx )
    target_link_libraries( StandardRecord_dict
                           PUBLIC StandardRecord ROOT::Core ROOT::Physics ROOT::TreePlayer
                         )
    target_include_directories( StandardRecord_dict INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
    )

    install( TARGETS StandardRecord_dict
             EXPORT duneanaobjTargets
             LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           )

    # rootcling emits these next to the build tree; ROOT looks for them beside
    # the installed library, so install them into the same libdir.
    install( FILES
             "${CMAKE_CURRENT_BINARY_DIR}/libStandardRecord_dict_rdict.pcm"
             "${CMAKE_CURRENT_BINARY_DIR}/libStandardRecord_dict.rootmap"
             DESTINATION ${CMAKE_INSTALL_LIBDIR}
           )

    # Setup CMake find_package related files
    install( EXPORT duneanaobjTargets
             DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
             NAMESPACE duneanaobj::
             FILE duneanaobjTargets.cmake
           )

    include(CMakePackageConfigHelpers)
    configure_package_config_file( ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
                                   "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfig.cmake"
                                   INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
                                   PATH_VARS CMAKE_INSTALL_LIBDIR
                                 )

    write_basic_package_version_file( "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
                                      VERSION ${PROJECT_VERSION}
                                      COMPATIBILITY SameMajorVersion
                                    )

    # Install these files too
    install( FILES
             "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfig.cmake"
             "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
             DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
           )
endif()
