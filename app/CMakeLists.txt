add_executable(duneanaobj_dumpevent duneanaobj_dumpevent.cxx)
target_link_libraries(duneanaobj_dumpevent duneanaobj::all ROOT::Tree ROOT::RIO)

install(TARGETS duneanaobj_dumpevent
  DESTINATION bin)
