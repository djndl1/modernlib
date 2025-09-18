set(CMAKE_CXX_STANDARD 23)
if (BUILD_TESTS_AS_CXX)
  set_source_files_properties(
    resmgmt_test.c
    PROPERTIES LANGUAGE CXX
    )
endif()

include_directories(AFTER ${CMAKE_SOURCE_DIR}/test)
link_libraries(modernlib)

add_executable(resmgmt_test resmgmt_test.c)
set_property(TARGET resmgmt_test PROPERTY C_EXTENSIONS ON)
add_test(NAME resmgmt_test
  COMMAND resmgmt_test)

add_executable(dyn_str_test dyn_str_test.c)
add_test(NAME dyn_str_test
  COMMAND dyn_str_test)

add_executable(data_buffer_test data_buffer_test.c)
add_test(NAME data_buffer_test
  COMMAND data_buffer_test)

add_executable(mem_ptr_test mem_ptr_test.c)
add_test(NAME mem_ptr_test
  COMMAND mem_ptr_test)

add_executable(utfconverter_test utfconverter_test.c)
add_test(NAME utfconverter_test
  COMMAND utfconverter_test)

add_executable(datetime_test datetime_test.c)
add_test(NAME datetime_test
  COMMAND datetime_test)

add_executable(cpp_build_test cpp_build_test.cpp)
