
# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

if(DEFINED CETMODULES_CURRENT_PROJECT_NAME)
    add_subdirectory(Proxy)
    add_subdirectory(Flat)

    cet_make_library( LIBRARY_NAME duneanaobj_StandardRecord
                      SOURCE       ${src_files}
                      LIBRARIES    ROOT::Core ROOT::Physics
                    )

    build_dictionary( duneanaobj_StandardRecord
                      DICTIONARY_LIBRARIES duneanaobj_StandardRecord
                    )

    install_headers()
    install_source()
elseif(SKIP_CET)
    # n.b.: missing Proxy, Plain and the dictionary!

    include(GNUInstallDirs)

    # Create and configure library target
    add_library( StandardRecord SHARED
                 ${src_files}
               )

    target_link_libraries( StandardRecord
                           ROOT::Core ROOT::Physics
                         )

    # Setup installation
    file( GLOB headers_files *.h )

    install( TARGETS StandardRecord EXPORT duneanaobjTargets DESTINATION ${CMAKE_INSTALL_LIBDIR} )
    install( FILES ${headers_files} DESTINATION "include/duneanaobj/StandardRecord" )

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
                                      VERSION 0.1.0
                                      COMPATIBILITY SameMajorVersion
                                    )

    # Install these files too
    install( FILES
             "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfig.cmake"
             "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
             DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
           )
else()
    add_library(duneanaobj_StandardRecord
                ${src_files})
    target_link_libraries(duneanaobj_StandardRecord
                     ROOT::Core ROOT::Physics )

    # n.b.: missing the dictionary and installation!
endif()
