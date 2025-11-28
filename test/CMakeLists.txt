add_executable(duneanaobj_dummyevent duneanaobj_dummyevent.cxx)
target_link_libraries(duneanaobj_dummyevent duneanaobj::All ROOT::Tree ROOT::RIO)