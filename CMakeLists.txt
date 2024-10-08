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
project(duneanaobj LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 03.06.01)

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


else()
    find_package(ROOT)
    include_directories(.)
endif()

add_subdirectory(duneanaobj)

cet_cmake_config()
