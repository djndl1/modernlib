include(CheckLibraryExists)

set(CMAKE_CXX_STANDARD 23)
if (BUILD_TESTS_AS_CXX)
  set_source_files_properties(
    dyn_str_test.c
    resmgmt_test.c
    data_buffer_test.c
    mem_ptr_test.c
    utfconverter_test.c
    datetime_test.c
    PROPERTIES LANGUAGE CXX
    )
endif()

# more robust check
check_library_exists(objc _NSConcreteStackBlock "" HAVE_OBJC_LIB)
check_library_exists(BlocksRuntime _NSConcreteStackBlock "" HAVE_BLOCKSRUNTIME_LIB)

if ((${CMAKE_C_COMPILER_ID} STREQUAL "Clang"))
  message(WARNING ${CMAKE_C_COMPILER_ID})
  add_compile_definitions(MODERNLIB_USE_CLANG_BLOCKS)
  add_compile_options(-fblocks)
  if (${HAVE_OBJC_LIB})
    link_libraries(objc)
  elseif(${HAVE_BLOCKSRUNTIME_LIB})
    link_libraries(BlocksRuntime)
  endif()
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
