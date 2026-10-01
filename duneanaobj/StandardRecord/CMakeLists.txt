set( PACKAGE duneanaobj_StandardRecord )
FILE( GLOB src_files *.cxx )

# For this directory only, pedantic option to catch uninitialized SR fields
# add_compile_options(-Weffc++)

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

    target_include_directories(duneanaobj_StandardRecord PUBLIC
      # for include "duneanaobj/" style includes at build time
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> # for classes_def.xml!!
      $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}> # for generated headers
        # for include "duneanaobj/" style includes for dependent projects
      $<INSTALL_INTERFACE:include>
    )

    build_dictionary( duneanaobj_StandardRecord
                      DICTIONARY_LIBRARIES duneanaobj_StandardRecord
                    )

    install_headers()
    install_source()
else()
    # n.b.: missing Proxy, Plain and the dictionary!

    include(GNUInstallDirs)

    # Create and configure library target
    add_library(StandardRecord SHARED ${src_files})

    target_link_libraries(StandardRecord
      PUBLIC duneanaobj::rootlibs
    )

    target_include_directories(StandardRecord PUBLIC
      # for include "duneanaobj/" style includes at build time
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
      # for include "duneanaobj/" style includes for dependent projects
      $<INSTALL_INTERFACE:include>
    )

    target_compile_definitions(StandardRecord
      PRIVATE
        DUNEANAOBJ_GIT_SHORTHASH="${duneanaobj_GITSHORTHASH8}"
        DUNEANAOBJ_VERSION="${PROJECT_VERSION}"
    )

    # ROOT I/O dictionary. The CET path gets this from cet's build_dictionary;
    # here we drive rootcling directly via ROOT's root_generate_dictionary,
    # fed the same classes.h / classes_def.xml selection file. The result is the
    # dictionary code gets added to the StandardRecord library plus the
    # .rootmap and _rdict.pcm that ROOT needs for autoloading at runtime.
    root_generate_dictionary(
      G__StandardRecord
      ${CMAKE_CURRENT_SOURCE_DIR}/classes.h
      MODULE StandardRecord
      LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/classes_def.xml
    )

    # useful for dependencies using FetchContent_MakeAvailable to pull this
    # package in at configure time and link using the same name as if it had
    # been exported/imported
    add_library(duneanaobj::StandardRecord ALIAS StandardRecord)
    install( TARGETS StandardRecord
      EXPORT duneanaobjTargets
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
    # rootcling emits these next to the build tree; ROOT looks for them beside
    # the installed library, so install them into the same libdir.
    install( FILES
             "${CMAKE_CURRENT_BINARY_DIR}/libStandardRecord_rdict.pcm"
             "${CMAKE_CURRENT_BINARY_DIR}/libStandardRecord.rootmap"
             DESTINATION ${CMAKE_INSTALL_LIBDIR}
           )
endif()

# Proxy/ and Flat/ generate their sources with gen_srproxy, so only descend into
# them when it was found.
if(GENERATE_PROXIES)

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

    add_subdirectory(Proxy)
    add_subdirectory(Flat)
else()
    message(WARNING "Could not find gen_srproxy; skipping the Proxy and Flat subdirectories")
endif()
