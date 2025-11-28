cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

project(duneanaobj VERSION 4.0.0 LANGUAGES CXX)

string(REPLACE "." ";" VERSION_LIST ${PROJECT_VERSION})
list(GET VERSION_LIST 0 duneanaobj_VERSION_MAJOR)
list(GET VERSION_LIST 1 duneanaobj_VERSION_MINOR)
list(GET VERSION_LIST 2 duneanaobj_VERSION_PATCH)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)

option(duneanaobj_PYTHON_ENABLED "Whether to build python bindings to proxy classes." OFF)

include(CPM)

SET(SRProxy_MIN_VERSION 0.46.0)

CPMFindPackage(
  NAME SRProxy
  GIT_TAG feature/Clingification_rebase3
  GITHUB_REPOSITORY luketpickering/SRProxy
  VERSION ${SRProxy_MIN_VERSION}
)

find_package(ROOT 6.20 REQUIRED)

add_subdirectory(duneanaobj)

add_library(duneanaobj_all INTERFACE)
set_target_properties(duneanaobj_all PROPERTIES EXPORT_NAME all)

target_link_libraries(duneanaobj_all INTERFACE
  duneanaobj::StandardRecordProxy
  duneanaobj::StandardRecordFlat
  duneanaobj::StandardRecord)

install(TARGETS duneanaobj_all EXPORT duneanaobj_targets)

add_library(duneanaobj::all ALIAS duneanaobj_all)

add_subdirectory(app)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/cmake/Templates/duneanaobjConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/duneanaobjConfig.cmake"
  INSTALL_DESTINATION this/is/ignored
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(EXPORT duneanaobj_targets
        NAMESPACE duneanaobj::
        DESTINATION lib/cmake/duneanaobj)
install(FILES "${PROJECT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/duneanaobjConfig.cmake"
        DESTINATION lib/cmake/duneanaobj)
