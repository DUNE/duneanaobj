GenSRProxy(
  HEADER duneanaobj/StandardRecord/StandardRecord.h
  FLAT
  OUTPUT_NAME SRFlat
  TARGETNAME caf::StandardRecord
  PROLOG ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h
  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../../.. ${ROOT_INCLUDE_DIRS}
  DEPENDENCIES ${SR_HEADER_FILE_FQPS})

add_library(duneanaobj_StandardRecordFlat SHARED SRFlat.cxx)
target_link_libraries(duneanaobj_StandardRecordFlat PUBLIC SRProxy::FlatTypes)
target_include_directories(duneanaobj_StandardRecordFlat PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../..>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../../..>
  $<INSTALL_INTERFACE:include>)

install(TARGETS duneanaobj_StandardRecordFlat EXPORT duneanaobj_targets DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SRFlat.h 
              ${CMAKE_CURRENT_BINARY_DIR}/FwdDeclare.h 
        DESTINATION include/duneanaobj/StandardRecord/Flat)

add_library(duneanaobj::StandardRecordFlat ALIAS duneanaobj_StandardRecordFlat)
