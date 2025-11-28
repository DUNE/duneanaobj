SET(GEN_PYTHON_BINDINGS)
if(duneanaobj_PYTHON_ENABLED)
  SET(GEN_PYTHON_BINDINGS EMIT_PYTHON_BINDINGS)
endif()

GenSRProxy(
  HEADER duneanaobj/StandardRecord/StandardRecord.h
  OUTPUT_NAME SRProxy
  TARGETNAME caf::StandardRecord
  PROLOG ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h
  EPILOG_FWD ${CMAKE_CURRENT_SOURCE_DIR}/EpilogFwd.h
  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../.. ${ROOT_INCLUDE_DIRS}
  DEPENDENCIES ${SR_HEADER_FILE_FQPS}
  ${GEN_PYTHON_BINDINGS}
  VVERBOSE)

add_library(duneanaobj_StandardRecordProxy SHARED SRProxy.cxx)
target_link_libraries(duneanaobj_StandardRecordProxy PUBLIC SRProxy::BasicTypes duneanaobj_StandardRecord)
target_include_directories(duneanaobj_StandardRecordProxy PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../..>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../../..>
  $<INSTALL_INTERFACE:include>)

install(TARGETS duneanaobj_StandardRecordProxy EXPORT duneanaobj_targets DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SRProxy.h
              ${CMAKE_CURRENT_BINARY_DIR}/FwdDeclare.h
        DESTINATION include/duneanaobj/StandardRecord/Proxy)

add_library(duneanaobj::StandardRecordProxy ALIAS duneanaobj_StandardRecordProxy)

if(duneanaobj_PYTHON_ENABLED)
  find_package(Python3 REQUIRED COMPONENTS Development Interpreter)

  # PYTHON PATHS
  set(duneanaobj_PYTHONPATH "python/${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")

  include(FetchContent)

  FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        f5fbe86 # release-3.0.1
  )

  FetchContent_MakeAvailable(pybind11)

  pybind11_add_module(pySRProxy SHARED SRProxy.pybind.cxx)

  target_include_directories(pySRProxy
    PRIVATE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include>
      )

  target_link_libraries(pySRProxy
    PRIVATE
      duneanaobj::StandardRecordProxy)

  install(TARGETS pySRProxy
      LIBRARY DESTINATION ${duneanaobj_PYTHONPATH})
endif()
