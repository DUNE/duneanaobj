# ======================================================================
#  larsoft main build file
#
#  cd .../path/to/build/directory
#  source .../path/to/larsoft/ups/setup_for_development <-d|-p>
#  cmake [-DCMAKE_INSTALL_PREFIX=/install/path]
#        -DCMAKE_BUILD_TYPE=$CETPKG_TYPE
#        $CETPKG_SOURCE
#  make
#  make test
#  make install
#  make package (builds distribution tarfile)
# ======================================================================


cmake_minimum_required (VERSION 3.20 FATAL_ERROR)
# cmake_policy(VERSION 3.18)

find_package(cetmodules REQUIRED)
project(duneanaobj VERSION 03.05.00 LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 03.05.00)

message(STATUS "\n\n  ==========================   ${PROJECT_NAME}   ==========================")

if(DEFINED ENV{UPS_DIR})
    # cetbuildtools contains our cmake modules

    include(CetCMakeEnv)
    cet_cmake_env()

    set_install_root()

    # The specification of the C++ standard is required because CET macros
    # set it to C++98 by default, and then override it depending on the
    # compiler version, as determined by the compiler qualifier.
    # Removing that qualifier, we need to supply that information manually,
    # and maintain it too.
    cet_set_compiler_flags(DIAGS CAUTIOUS
        WERROR
        NO_UNDEFINED
        ALLOW_DEPRECATIONS
        EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs -Wno-undefined-var-template -I $ENV{CLANG_FQ_DIR}/include/c++/v1
    )

    cet_report_compiler_flags()

    # these are minimum required versions, not the actual product versions
    find_package(ROOT 6.00.00 REQUIRED)

    include(BuildDictionary)

    # packaging utility

    cet_cmake_config() # Put this here but am not sure... probably not going to see a lot of use anyway /shrug
else()
    # This is where the real stuff happens, ain't nobody usin' this cet sit
    find_package(ROOT)
    include(BuildDictionary)
    include_directories(.)

    # Include module with function 'write_basic_package_version_file'
    include(CMakePackageConfigHelpers)

    # Write the ConfigVersion.cmake file which can be used to
    # check if a version meets the requested properties.
    write_basic_package_version_file(duneanaobjConfigVersion.cmake COMPATIBILITY SameMajorVersion)

    # Write the Config.cmake file so that a user package can
    # access this with find_package.
    configure_package_config_file(PackageConfig.cmake.in duneanaobjConfig.cmake PATH_VARS CMAKE_INSTALL_PREFIX INSTALL_DESTINATION lib/cmake/duneanaobj)

    # Install the config files.
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfigVersion.cmake DESTINATION lib/cmake/duneanaobj INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install(EXPORT duneanaobjTargets NAMESPACE duneanaobj:: DESTINATION lib/cmake/duneanaobj)# INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

add_subdirectory(duneanaobj)
