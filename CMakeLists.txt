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

#find_package(cetmodules REQUIRED)
project(duneanaobj LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 03.05.00)

message(STATUS "\n\n  ==========================   ${PROJECT_NAME}   ==========================")

find_package(ROOT)
#find_package(SRPROXY)
set(SRPROXY_INC, "$ENV(SRPROXY_DIR)")

include_directories(.)
include_directories(SRPROXY_INC)

add_subdirectory(duneanaobj)
#add_subdirectory(.)

