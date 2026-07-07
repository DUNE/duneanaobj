FILE(GLOB SR_DEPENDENCIES duneanaobj/StandardRecord/*.h)

add_custom_command(# Rebuild if anything in StandardRecord/ changes
                   DEPENDS ${SR_DEPENDENCIES}
                   OUTPUT FlatRecord.cxx FlatRecord.h FwdDeclare.h
                   COMMAND gen_srproxy --flat -i duneanaobj/StandardRecord/StandardRecord.h -o FlatRecord --target caf::StandardRecord --include-path ${PROJECT_SOURCE_DIR}:$ENV{ROOT_INCLUDE_PATH}:$ENV{ROOT_INC} --output-path duneanaobj/StandardRecord/Flat/ --prolog ${CMAKE_CURRENT_SOURCE_DIR}/Prolog.h --extra-cflags ' -D_Float16=short -fsized-deallocation'
  )


include_directories($ENV{SRPROXY_INC})
if(NOT SKIP_CET)
    cet_make_library(LIBRARY_NAME duneanaobj_StandardRecordFlat
                     SOURCE       FlatRecord.cxx
                     LIBRARIES    ${ROOT_BASIC_LIB_LIST} ROOT::TreePlayer
                     )

    if (DEFINED ENV{MRB_BUILDDIR} AND NOT "$ENV{MRB_BUILDDIR}" STREQUAL "")
        set(builddir $ENV{MRB_BUILDDIR}/duneanaobj)
    else()
      if(DEFINED ENV{SPACK_ENV} AND NOT "$ENV{SPACK_ENV}" STREQUAL "")
        message(STATUS "SPACK_ENV = $ENV{SPACK_ENV}")
        include_directories($ENV{SPACK_ENV}/.spack-env/view/include)
        set(builddir $ENV{SPACK_ENV}/../build/duneanaobj/)
        include_directories($ENV{ROOT_INCLUDE_PATH})
      else()
        set(builddir ${CMAKE_BINARY_DIR})
      endif()
    endif()
    install_headers(EXTRAS ${builddir}/duneanaobj/StandardRecord/Flat/FlatRecord.h ${builddir}/duneanaobj/StandardRecord/Flat/FwdDeclare.h)
else()
    add_library(duneanaobj_StandardRecordFlat
                FlatRecord.cxx)
    target_link_libraries(duneanaobj_StandardRecordFlat ${ROOT_BASIC_LIB_LIST} ROOT::TreePlayer)

    install(FILES ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Flat/FlatRecord.h ${CMAKE_BINARY_DIR}/duneanaobj/StandardRecord/Flat/FwdDeclare.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/duneanaobj)

endif()
