FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

# Locate the SRProxy generator. Fall back to $SRPROXY_DIR/bin if it isn't on the PATH.
find_program(GEN_SRPROXY gen_srproxy HINTS $ENV{SRPROXY_DIR}/bin)
if(NOT GEN_SRPROXY)
    message(WARNING "Could not find gen_srproxy; skipping SRProxy generation and library build")
    return()
endif()

add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT SRProxy.cxx SRProxy.h FwdDeclare.h
                   COMMAND ${GEN_SRPROXY} -i duneanaobj/StandardRecord/StandardRecord.h -o SRProxy --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INCLUDE_PATH}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Proxy/ --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --epilog-fwd ${CMAKE_CURRENT_SOURCE_DIR}/EpilogFwd.h --extra-cflags ' -D_Float16=short -fsized-deallocation'
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
    endif()
    if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/../../local/.spack-env/view)
        message(STATUS "env view dir  ${PROJECT_SOURCE_DIR}/../../local/.spack-env/view")
        include_directories(${PROJECT_SOURCE_DIR}/../../local/.spack-env/view/include)
        include_directories($ENV{ROOT_INCLUDE_PATH})
    endif()
    install_headers(EXTRAS ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/SRProxy.h ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/FwdDeclare.h)
else()
    # GNUInstallDirs is included by StandardRecord/CMakeLists.txt, but that runs
    # after this subdirectory, so pull it in here for CMAKE_INSTALL_*DIR.
    include(GNUInstallDirs)

    add_library(duneanaobj_StandardRecordProxy
                SRProxy.cxx Instantiations.cxx)
    target_link_libraries(duneanaobj_StandardRecordProxy ROOT::Core ROOT::Physics ROOT::TreePlayer)
    target_include_directories(duneanaobj_StandardRecordProxy INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>)

    install(TARGETS duneanaobj_StandardRecordProxy
            EXPORT duneanaobjTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

    install(FILES ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/SRProxy.h ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Proxy/FwdDeclare.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/duneanaobj)
endif()

