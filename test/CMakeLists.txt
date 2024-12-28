include_directories(AFTER ${CMAKE_SOURCE_DIR}/test)

add_executable(resmgmt_test resmgmt_test.c)
add_test(NAME resmgmt_test
  COMMAND resmgmt_test)
