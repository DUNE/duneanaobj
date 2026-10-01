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

# See https://cmake.org/cmake/help/latest/policy/CMP0048.html#policy:CMP0048
# as of Feb 2026, dunesw mrb-built products set the version in the
# CMAKE_PROJECT_VERSION_STRING set, and not in the project line.
# but we must be using the OLD policy.  Setting the version string
# here will get overwritten by the project line with the same value when
# we migrate to the NEW policy

project(duneanaobj VERSION 04.01.01 LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 04.01.00)

string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 duneanaobj_VERSION_MAJOR)
list(GET VERSION_LIST 1 duneanaobj_VERSION_MINOR)
list(GET VERSION_LIST 2 duneanaobj_VERSION_PATCH)

message(STATUS "\n\n  ==========================   ${PROJECT_NAME}   ==========================")

option(SKIP_CET "Build without CET/cetmodules dependencies" OFF)

if(DEFINED ENV{UPS_DIR})
   set(SKIP_CET false)
endif()

if(NOT SKIP_CET)
    find_package(cetmodules REQUIRED)
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


else()
    find_package(ROOT 6.20 REQUIRED)
endif()

# package up the root dependencies into an interface target
add_library(duneanaobj_rootlibs INTERFACE)
set_target_properties(duneanaobj_rootlibs PROPERTIES EXPORT_NAME rootlibs)
target_link_libraries(duneanaobj_rootlibs INTERFACE ROOT::Core ROOT::Physics ROOT::TreePlayer)
install(TARGETS duneanaobj_rootlibs EXPORT duneanaobjTargets)
add_library(duneanaobj::rootlibs ALIAS duneanaobj_rootlibs)

# Locate the SRProxy code generator. Prefer a find_package()'able
# SRProxy (which exports the SRProxy::SRProxy target carrying its headers), and
# cascade back to the older $SRPROXY_INC / $SRPROXY_DIR layout otherwise.
SET(GENERATE_PROXIES FALSE)
find_package(SRProxy QUIET CONFIG)
if(SRProxy_FOUND)
    message(STATUS "Found SRProxy CMake package at ${SRProxy_DIR}")
    # SRProxy exports its headers but not the gen_srproxy executable,
    # so look for it under the package's install prefix (then fall back to $SRPROXY_DIR/bin).
    get_filename_component(SRPROXY_PREFIX "${SRProxy_DIR}/../../.." ABSOLUTE)
    find_program(GEN_SRPROXY gen_srproxy HINTS "${SRPROXY_PREFIX}/bin" $ENV{SRPROXY_DIR}/bin)
else()
    message(STATUS "SRProxy CMake package not found; using $SRPROXY_INC / $SRPROXY_DIR")
    find_program(GEN_SRPROXY gen_srproxy HINTS $ENV{SRPROXY_DIR}/bin)
    if (GEN_SRPROXY)
      add_library(SRProxy::SRProxy IMPORTED INTERFACE)
      target_include_directories(SRProxy::SRProxy INTERFACE $ENV{SRPROXY_INC})
    endif()
endif()

if(GEN_SRPROXY)
  SET(GENERATE_PROXIES TRUE)
endif()

add_subdirectory(duneanaobj)

if (NOT SKIP_CET)
    cet_cmake_config()
else()
    # Setup installation. Install the headers under include/duneanaobj/StandardRecord/
    # so the "duneanaobj/StandardRecord/..." include paths used throughout the
    # sources resolve against the exported include/ interface. (PUBLIC_HEADER would
    # flatten them straight into include/, which does not match those paths.)
    file( GLOB headers_files *.h )
    install( FILES ${headers_files} DESTINATION include/duneanaobj/StandardRecord )

    # Setup CMake find_package related files
    install( EXPORT duneanaobjTargets
             DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
             NAMESPACE duneanaobj::
             FILE duneanaobjTargets.cmake
           )

    include(CMakePackageConfigHelpers)
    configure_package_config_file( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Templates/Config.cmake.in
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
