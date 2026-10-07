FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

# GEN_SRPROXY and the SRProxy include path are set up by the parent
# StandardRecord/CMakeLists.txt, which only descends here when the generator
# was found.
add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT FlatRecord.cxx FlatRecord.h FwdDeclare.h
                   COMMAND ${GEN_SRPROXY} --flat -i duneanaobj/StandardRecord/StandardRecord.h -o FlatRecord --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INCLUDE_PATH}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Flat/ --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --extra-cflags "${SRPROXY_CASTXML_CFLAGS}"
  )

if(NOT SKIP_CET)
    message(STATUS "CETMODULES_CURRENT_PROJECT_NAME = '${CETMODULES_CURRENT_PROJECT_NAME}'")
    cet_make_library(LIBRARY_NAME duneanaobj_StandardRecordFlat
                     SOURCE       FlatRecord.cxx
                     LIBRARIES    SRProxy::SRProxy ROOT::Core ROOT::Physics ROOT::TreePlayer
                     )

    if (DEFINED ENV{MRB_BUILDDIR} AND NOT "$ENV{MRB_BUILDDIR}" STREQUAL "")
        message(STATUS "MRB_BUILDDIR = $ENV{MRB_BUILDDIR}")
    endif()
    if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/../../local/.spack-env/view)
        message(STATUS "env view dir ${PROJECT_SOURCE_DIR}/../../local/.spack-env/view")
        include_directories(${PROJECT_SOURCE_DIR}/../../local/.spack-env/view/include)
        include_directories($ENV{ROOT_INCLUDE_PATH})
    endif()
    install_headers(EXTRAS ${CMAKE_CURRENT_BINARY_DIR}/FlatRecord.h ${CMAKE_CURRENT_BINARY_DIR}/FwdDeclare.h)
else()

    add_library(duneanaobj_StandardRecordFlat SHARED FlatRecord.cxx)
    set_target_properties(duneanaobj_StandardRecordFlat PROPERTIES EXPORT_NAME StandardRecordFlat)
    target_link_libraries(duneanaobj_StandardRecordFlat PUBLIC StandardRecord)

    # required to find the generated header at build time
    target_include_directories(duneanaobj_StandardRecordFlat PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../../..)
    if(TARGET SRProxy::SRProxy)
        # Propagate SRProxy to consumers of the exported target; duneanaobjConfig
        # re-finds it via find_dependency(SRProxy).
        target_link_libraries(duneanaobj_StandardRecordFlat PUBLIC SRProxy::SRProxy)
    endif()

    install(TARGETS duneanaobj_StandardRecordFlat
            EXPORT duneanaobjTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    add_library(duneanaobj::StandardRecordFlat ALIAS duneanaobj_StandardRecordFlat)

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FlatRecord.h ${CMAKE_CURRENT_BINARY_DIR}/FwdDeclare.h
            DESTINATION include/duneanaobj/StandardRecord/Flat)

endif()
