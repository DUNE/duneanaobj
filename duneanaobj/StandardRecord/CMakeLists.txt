execute_process(COMMAND git rev-parse --short=8 HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..
  OUTPUT_VARIABLE duneanaobj_GITSHORTHASH8
  RESULT_VARIABLE GIT_CMD_SUCCESS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT GIT_CMD_SUCCESS EQUAL 0)
  message(FATAL_ERROR "Failed to run git rev-parse --short=8 HEAD in ${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif()

configure_file(StandardRecord.cxx.in ${CMAKE_CURRENT_BINARY_DIR}/StandardRecord.cxx @ONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)

ROOT_GENERATE_DICTIONARY(StandardRecordDict StandardRecord.h
  LINKDEF classes_def.xml)

SET(SR_IMPL_FILES
  Navigate.cxx
  SRFD.cxx
  SRGArTrack.cxx
  SRGlobal.cxx
  SRInteraction.cxx
  SRLorentzVector.cxx
  SRMeta.cxx
  SRMINERvA.cxx
  SRNDLAr.cxx
  SRSystParamHeader.cxx
  SRTrack.cxx
  SRTruthBranch.cxx
  SRVector3D.cxx
  SRWeightGlobal.cxx
  StandardRecord.cxx
  ${CMAKE_CURRENT_BINARY_DIR}/StandardRecordDict.cxx
)

SET(SR_HEADER_FILES
  SRBeamBranch.h
  SRCommonRecoBranch.h
  SRCVNScoreBranch.h
  SRDetectorMetaBranch.h
  SRDirectionBranch.h
  SREnums.h
  SRFD.h
  SRFDBranch.h
  SRGAr.h
  SRGArECAL.h
  SRGArTrack.h
  SRGlobal.h
  SRInteraction.h
  SRInteractionBranch.h
  SRLorentzVector.h
  SRMeta.h
  SRMINERvA.h
  SRNDAssnBranch.h
  SRNDBranch.h
  SRNDLAr.h
  SRNDShowerAssn.h
  SRNDTrackAssn.h
  SRNeutrinoEnergyBranch.h
  SRNeutrinoHypothesisBranch.h
  SROpticalFlash.h
  SRPFP.h
  SRRecoParticle.h
  SRRecoParticlesBranch.h
  SRSAND.h
  SRShower.h
  SRSystParamHeader.h
  SRTMS.h
  SRTrack.h
  SRTrueInteraction.h
  SRTrueParticle.h
  SRTruthBranch.h
  SRVector3D.h
  SRWeightGlobal.h
)

add_library(duneanaobj_StandardRecord SHARED ${SR_IMPL_FILES})
target_link_libraries(duneanaobj_StandardRecord PUBLIC ROOT::Physics ROOT::MathCore)
target_include_directories(duneanaobj_StandardRecord PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
  $<INSTALL_INTERFACE:include>)
target_include_directories(duneanaobj_StandardRecord PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> #root puts this in the dictionary
  )
set_target_properties(duneanaobj_StandardRecord PROPERTIES EXPORT_NAME StandardRecord)
install(TARGETS duneanaobj_StandardRecord EXPORT duneanaobj_targets DESTINATION lib)
install(FILES ${SR_HEADER_FILES} DESTINATION include/duneanaobj/StandardRecord)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/libStandardRecordDict_rdict.pcm
    ${CMAKE_CURRENT_BINARY_DIR}/libStandardRecordDict.rootmap
  DESTINATION lib)

add_library(duneanaobj::StandardRecord ALIAS duneanaobj_StandardRecord)

# get the location of these to allow the code generation scripts to properly set up
# dependencies
SET(SR_HEADER_FILE_FQPS)
foreach(HDR ${SR_HEADER_FILES})
  LIST(APPEND SR_HEADER_FILE_FQPS ${CMAKE_CURRENT_SOURCE_DIR}/${HDR})
endforeach()

add_subdirectory(Proxy)
add_subdirectory(Flat)
