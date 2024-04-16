FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT FlatRecord.cxx FlatRecord.h FwdDeclare.h
                   COMMAND gen_srproxy --flat -i duneanaobj/StandardRecord/StandardRecord.h -o FlatRecord --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Flat/ --extra-cflags ' -D_Float16=short'
  )

include_directories($ENV{SRPROXY_INC})

cet_make_library(LIBRARY_NAME duneanaobj_StandardRecordFlat
                 SOURCE       FlatRecord.cxx
                 LIBRARIES    ROOT::Core ROOT::Physics ROOT::TreePlayer
                 )

install_headers(EXTRAS ${CMAKE_BINARY_DIR}/duneanaobj/duneanaobj/StandardRecord/Flat/FlatRecord.h ${CMAKE_BINARY_DIR}/duneanaobj/duneanaobj/StandardRecord/Flat/FwdDeclare.h)
