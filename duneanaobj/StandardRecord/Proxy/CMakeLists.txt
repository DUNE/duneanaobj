FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT SRProxy.cxx SRProxy.h FwdDeclare.h
                   COMMAND gen_srproxy -i duneanaobj/StandardRecord/StandardRecord.h -o SRProxy --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INCLUDE_PATH}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Proxy/ --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --epilog-fwd ${CMAKE_CURRENT_SOURCE_DIR}/EpilogFwd.h --extra-cflags ' -D_Float16=short -fsized-deallocation'
  )

include_directories($ENV{SRPROXY_INC})

# This is a very picky error buried inside template instantiations
#add_definitions(-Wno-int-in-bool-context)

if(NOT SKIP_CET)
    message(STATUS "CETMODULES_CURRENT_PROJECT_NAME = '${CETMODULES_CURRENT_PROJECT_NAME}'")
    cet_make_library(LIBRARY_NAME duneanaobj_StandardRecordProxy
            SOURCE       SRProxy.cxx Instantiations.cxx
            LIBRARIES    ROOT::Core ROOT::Physics ROOT::TreePlayer)

    if (DEFINED ENV{MRB_BUILDDIR} AND NOT "$ENV{MRB_BUILDDIR}" STREQUAL "")
        message(STATUS "MRB_BUILDDIR = $ENV{MRB_BUILDDIR}")
        set(builddir $ENV{MRB_BUILDDIR}/duneanaobj)
    else()
        set(builddir ${CMAKE_BINARY_DIR})
    endif()
    if(DEFINED ENV{SPACK_ENV})
        message(STATUS "SPACK_ENV = $ENV{SPACK_ENV}")
        include_directories($ENV{SPACK_ENV}/.spack-env/view/include)
        set(builddir $ENV{SPACK_ENV}/../build/duneanaobj/)
        include_directories($ENV{ROOT_INCLUDE_PATH})
    else()
        set(builddir ${CMAKE_BINARY_DIR})
    endif()
    install_headers(EXTRAS ${builddir}/duneanaobj/StandardRecord/Proxy/SRProxy.h ${builddir}/duneanaobj/StandardRecord/Proxy/FwdDeclare.h)
else()
    add_library(duneanaobj_StandardRecordProxy
                SRProxy.cxx Instantiations.cxx)
    target_link_libraries(duneanaobj_StandardRecordProxy ROOT::Core ROOT::Physics ROOT::TreePlayer)

    install(FILES ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/SRProxy.h ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/FwdDeclare.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/duneanaobj)
endif()

