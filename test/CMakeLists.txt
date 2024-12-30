include_directories(AFTER ${CMAKE_SOURCE_DIR}/test)
link_libraries(modernlib)

add_executable(resmgmt_test resmgmt_test.c)
add_test(NAME resmgmt_test
  COMMAND resmgmt_test)

add_executable(dyn_str_test dyn_str_test.c)
add_test(NAME dyn_str_test
  COMMAND dyn_str_test)
