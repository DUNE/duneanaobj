FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

# Locate the SRProxy generator. Fall back to $SRPROXY_DIR/bin if it isn't on the PATH.
find_program(GEN_SRPROXY gen_srproxy HINTS $ENV{SRPROXY_DIR}/bin)
if(NOT GEN_SRPROXY)
    message(WARNING "Could not find gen_srproxy; skipping FlatRecord generation and library build")
    return()
endif()

add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT FlatRecord.cxx FlatRecord.h FwdDeclare.h
                   COMMAND ${GEN_SRPROXY} --flat -i duneanaobj/StandardRecord/StandardRecord.h -o FlatRecord --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INCLUDE_PATH}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Flat/ --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --extra-cflags ' -D_Float16=short -fsized-deallocation'
  )


include_directories($ENV{SRPROXY_INC})

if(NOT SKIP_CET)
    message(STATUS "CETMODULES_CURRENT_PROJECT_NAME = '${CETMODULES_CURRENT_PROJECT_NAME}'")
    cet_make_library(LIBRARY_NAME duneanaobj_StandardRecordFlat
                     SOURCE       FlatRecord.cxx
                     LIBRARIES    ROOT::Core ROOT::Physics ROOT::TreePlayer
                     )

    if (DEFINED ENV{MRB_BUILDDIR} AND NOT "$ENV{MRB_BUILDDIR}" STREQUAL "")
        message(STATUS "MRB_BUILDDIR = $ENV{MRB_BUILDDIR}")
    endif()
    if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/../../local/.spack-env/view)
        message(STATUS "env view dir ${PROJECT_SOURCE_DIR}/../../local/.spack-env/view")
        include_directories(${PROJECT_SOURCE_DIR}/../../local/.spack-env/view/include)
        include_directories($ENV{ROOT_INCLUDE_PATH})
    endif()
    install_headers(EXTRAS ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Flat/FlatRecord.h ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Flat/FwdDeclare.h)
else()
    add_library(duneanaobj_StandardRecordFlat
                FlatRecord.cxx)
    target_link_libraries(duneanaobj_StandardRecordFlat ROOT::Core ROOT::Physics ROOT::TreePlayer)

    install(FILES ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Flat/FlatRecord.h ${PROJECT_BINARY_DIR}/duneanaobj/StandardRecord/Flat/FwdDeclare.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/duneanaobj)

endif()
