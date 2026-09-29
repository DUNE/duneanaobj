FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

# GEN_SRPROXY and the SRProxy include path are set up by the parent
# StandardRecord/CMakeLists.txt, which only descends here when the generator
# was found.
add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT SRProxy.cxx SRProxy.h FwdDeclare.h
                   COMMAND ${GEN_SRPROXY} -i duneanaobj/StandardRecord/StandardRecord.h -o SRProxy --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INCLUDE_PATH}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Proxy/ --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --epilog-fwd ${CMAKE_CURRENT_SOURCE_DIR}/EpilogFwd.h --extra-cflags "${SRPROXY_CASTXML_CFLAGS}"
  )

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
    install_headers(EXTRAS ${CMAKE_CURRENT_BINARY_DIR}/SRProxy.h
                           ${CMAKE_CURRENT_BINARY_DIR}/FwdDeclare.h)
else()
    # GNUInstallDirs is included by StandardRecord/CMakeLists.txt, but that runs
    # after this subdirectory, so pull it in here for CMAKE_INSTALL_*DIR.
    include(GNUInstallDirs)

    add_library(duneanaobj_StandardRecordProxy SHARED SRProxy.cxx Instantiations.cxx)
    target_link_libraries(duneanaobj_StandardRecordProxy PUBLIC StandardRecord)

    # required to find the generated header at build time
    target_include_directories(duneanaobj_StandardRecordProxy PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../../..)
    if(TARGET SRProxy::SRProxy)
        # Propagate SRProxy to consumers of the exported target; duneanaobjConfig
        # re-finds it via find_dependency(SRProxy).
        target_link_libraries(duneanaobj_StandardRecordProxy PUBLIC SRProxy::SRProxy)
    endif()

    # If we are using the python version of SRProxy, then there are no basic
    #   types precompiled
    if(NOT TARGET SRProxy::BasicTypes)
      target_compile_definitions(duneanaobj_StandardRecordProxy PRIVATE NO_PRECOMPILED_SRBASICTYPES)
    endif()

    install(TARGETS duneanaobj_StandardRecordProxy
            EXPORT duneanaobjTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SRProxy.h
                  ${CMAKE_CURRENT_BINARY_DIR}/FwdDeclare.h
            DESTINATION include/duneanaobj/StandardRecord/Proxy)
endif()

