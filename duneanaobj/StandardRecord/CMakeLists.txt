
# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

    add_subdirectory(Proxy)
    add_subdirectory(Flat)

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
