FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT SRProxy.cxx SRProxy.h FwdDeclare.h
                   COMMAND gen_srproxy -i duneanaobj/StandardRecord/StandardRecord.h -o SRProxy --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INC} --output-path ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Proxy --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --epilog-fwd ${CMAKE_CURRENT_SOURCE_DIR}/EpilogFwd.h --extra-cflags ' -D_Float16=short -fsized-deallocation'
  )

include_directories($ENV{SRPROXY_INC})

# This is a very picky error buried inside template instantiations
#add_definitions(-Wno-int-in-bool-context)

add_library(duneanaobj_StandardRecordProxy
            SRProxy.cxx Instantiations.cxx)
target_link_libraries(duneanaobj_StandardRecordProxy ${ROOT_BASIC_LIB_LIST} ROOT::TreePlayer)

install(FILES ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/SRProxy.h ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/FwdDeclare.h
        DESTINATION ${CMAKE_INSTALL_PREFIX}/duneanaobj)
