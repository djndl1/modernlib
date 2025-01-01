cmake_minimum_required(VERSION 3.12)

project(modernlib)

include_directories(AFTER ${modernlib_SOURCE_DIR}/include)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/Wall)
else()
  add_compile_options(-Wall -Wstrict-aliasing -Wno-unused-function)
endif()

set(libsrc
  src/allocator.c
  src/data_buffer.c
  src/dyn_cstr.c
  src/stopwatch.c
  src/dyn_wchar_array.c
  src/dyn_char_array.c
  src/dyn_cwstr.c
)

add_library(modernlib SHARED
  ${libsrc}
)
target_compile_definitions(modernlib PRIVATE MODERNLIB_SHARED_BUILD)

set_target_properties(modernlib PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(modernlib_static STATIC
  ${libsrc}
)
target_compile_definitions(modernlib_static PRIVATE MODERNLIB_STATIC_BUILD)

enable_testing()
subdirs(test)
