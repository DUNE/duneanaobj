
# for classes_def.xml!!
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

# Locate the SRProxy code generator and runtime headers once, here, so both the
# Proxy/ and Flat/ subdirectories share the result. Prefer a find_package()'able
# SRProxy (which exports the SRProxy::SRProxy target carrying its headers), and
# cascade back to the older $SRPROXY_INC / $SRPROXY_DIR layout otherwise.
find_package(SRProxy QUIET CONFIG)
if(SRProxy_FOUND)
    message(STATUS "Found SRProxy CMake package at ${SRProxy_DIR}")
    # SRProxy exports its headers but not the gen_srproxy executable,
    # so look for it under the package's install prefix (then fall back to $SRPROXY_DIR/bin).
    get_filename_component(SRPROXY_PREFIX "${SRProxy_DIR}/../../.." ABSOLUTE)
    find_program(GEN_SRPROXY gen_srproxy HINTS "${SRPROXY_PREFIX}/bin" $ENV{SRPROXY_DIR}/bin)
    get_target_property(SRPROXY_INCLUDE_DIRS SRProxy::SRProxy INTERFACE_INCLUDE_DIRECTORIES)
    include_directories(${SRPROXY_INCLUDE_DIRS})
else()
    message(STATUS "SRProxy CMake package not found; using $SRPROXY_INC / $SRPROXY_DIR")
    find_program(GEN_SRPROXY gen_srproxy HINTS $ENV{SRPROXY_DIR}/bin)
    include_directories($ENV{SRPROXY_INC})
endif()

# gen_srproxy drives castxml to parse the StandardRecord headers. castxml 0.6.x
# (clang-based, emulating gcc) can't parse gcc-13's libstdc++/glibc as-is: it
# represents the _FloatN types as non-convertible structs, which breaks <cmath>'s
# __iseqsig overloads, and its clang trips over the __assume__ statement attribute
# in <bits/stl_bvector.h>. Presenting as clang (-D__clang__=1) makes libstdc++
# skip the __assume__ path, and remapping each _FloatN to a distinct convertible
# builtin sidesteps the __iseqsig failures. None of these types appear in
# StandardRecord, so this only affects how the system headers parse, not the
# generated proxies. (Shared by both Proxy/ and Flat/ via inheritance.)
# -Wno-macro-redefined silences the expected warnings from the _FloatN redefines.
#  Only gcc >= 13 pulls in the <cmath>/<bits> constructs that need the remaps here.
#  On older gcc, the _FloatN remaps instead clash with the _real_ `typedef float _Float32;`,
#  so we keep a more minimal set of flags in that case.
#  fixme: maybe we can drop this block someday if we can guarantee everybody's using new enough castxml to parse the gcc headers correctly..........
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
    CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "13.0")
  set(SRPROXY_CASTXML_CFLAGS "-D__clang__=1 -D_Float16=short -D_Float32=int -D_Float64=long -D_Float128=__int128 -D_Float32x=char -D_Float64x=wchar_t -D_Float128x=char16_t -fsized-deallocation -Wno-macro-redefined")
else()
  set(SRPROXY_CASTXML_CFLAGS "-D_Float16=short -fsized-deallocation")
endif()
# Proxy/ and Flat/ generate their sources with gen_srproxy, so only descend into
# them when it was found.
if(GEN_SRPROXY)
    add_subdirectory(Proxy)
    add_subdirectory(Flat)
else()
    message(WARNING "Could not find gen_srproxy; skipping the Proxy and Flat subdirectories")
endif()

execute_process(COMMAND git rev-parse --short=8 HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../..
  OUTPUT_VARIABLE duneanaobj_GITSHORTHASH8
  RESULT_VARIABLE GIT_CMD_SUCCESS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT GIT_CMD_SUCCESS EQUAL 0)
  message(STATUS "Failed to run git rev-parse --short=8 HEAD in ${CMAKE_CURRENT_SOURCE_DIR}/../..")
  SET(duneanaobj_GITSHORTHASH8 "none -- release build?")
endif()

if(NOT SKIP_CET)
    cet_make_library( LIBRARY_NAME duneanaobj_StandardRecord
                      SOURCE       ${src_files}
                      LIBRARIES    ROOT::Core ROOT::Physics
                    )

    target_compile_definitions(duneanaobj_StandardRecord
      PRIVATE
        DUNEANAOBJ_GIT_SHORTHASH="${duneanaobj_GITSHORTHASH8}"
        DUNEANAOBJ_VERSION="${PROJECT_VERSION}"
    )

    build_dictionary( duneanaobj_StandardRecord
                      DICTIONARY_LIBRARIES duneanaobj_StandardRecord
                    )

    install_headers()
    install_source()
else()
    # n.b.: missing Proxy, Plain and the dictionary!

    include(GNUInstallDirs)

    # ROOT I/O dictionary. The CET path gets this from cet's build_dictionary;
    # here we drive rootcling directly via ROOT's root_generate_dictionary,
    # fed the same classes.h / classes_def.xml selection file. The result is a
    # standalone StandardRecord_dict library (exported as
    # duneanaobj::StandardRecord_dict) plus the .rootmap and _rdict.pcm that
    # ROOT needs for autoloading at runtime.
    root_generate_dictionary( G__StandardRecord
                              ${CMAKE_CURRENT_SOURCE_DIR}/classes.h
                              MODULE StandardRecord_dict
                              LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/classes_def.xml
                            )

    add_library( StandardRecord_dict SHARED G__StandardRecord.cxx )
    target_link_libraries( StandardRecord_dict
                           PUBLIC ROOT::Physics ROOT::TreePlayer ROOT::Core
                         )
    target_include_directories( StandardRecord_dict INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
    )
    target_compile_definitions(StandardRecord_dict
      PRIVATE
        DUNEANAOBJ_GIT_SHORTHASH="${duneanaobj_GITSHORTHASH8}"
        DUNEANAOBJ_VERSION="${PROJECT_VERSION}"
    )

    # Create and configure library target
    add_library( StandardRecord SHARED
                 ${src_files}
               )

    target_link_libraries( StandardRecord
                           PUBLIC StandardRecord_dict
                         )
    target_include_directories(StandardRecord INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:include>
    )

    target_compile_definitions(StandardRecord
      PRIVATE
        DUNEANAOBJ_GIT_SHORTHASH="${duneanaobj_GITSHORTHASH8}"
        DUNEANAOBJ_VERSION="${PROJECT_VERSION}"
    )

    # useful for dependencies using FetchContent_MakeAvailable to pull this
    # package in at configure time and link using the same name as if it had
    # been exported/imported
    add_library(duneanaobj::StandardRecord ALIAS StandardRecord)

    install( TARGETS StandardRecord StandardRecord_dict EXPORT duneanaobjTargets LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    # rootcling emits these next to the build tree; ROOT looks for them beside
    # the installed library, so install them into the same libdir.
    install( FILES
             "${CMAKE_CURRENT_BINARY_DIR}/libStandardRecord_dict_rdict.pcm"
             "${CMAKE_CURRENT_BINARY_DIR}/libStandardRecord_dict.rootmap"
             DESTINATION ${CMAKE_INSTALL_LIBDIR}
           )

    # Setup installation. Install the headers under include/duneanaobj/StandardRecord/
    # so the "duneanaobj/StandardRecord/..." include paths used throughout the
    # sources resolve against the exported include/ interface. (PUBLIC_HEADER would
    # flatten them straight into include/, which does not match those paths.)
    file( GLOB headers_files *.h )
    install( FILES ${headers_files} DESTINATION include/duneanaobj/StandardRecord )

    # Setup CMake find_package related files
    install( EXPORT duneanaobjTargets
             DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
             NAMESPACE duneanaobj::
             FILE duneanaobjTargets.cmake
           )

    include(CMakePackageConfigHelpers)
    configure_package_config_file( ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
                                   "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfig.cmake"
                                   INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
                                   PATH_VARS CMAKE_INSTALL_LIBDIR
                                 )

    write_basic_package_version_file( "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
                                      VERSION ${PROJECT_VERSION}
                                      COMPATIBILITY SameMajorVersion
                                    )

    # Install these files too
    install( FILES
             "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfig.cmake"
             "${CMAKE_CURRENT_BINARY_DIR}/duneanaobjConfigVersion.cmake"
             DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/duneanaobj"
           )
endif()
