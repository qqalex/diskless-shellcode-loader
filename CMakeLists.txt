cmake_minimum_required(VERSION 3.31.0-rc3)
project(beacon)

# Debug
set(CMAKE_C_FLAGS_DEBUG_INIT "-Wall")
# Release
set(CMAKE_C_FLAGS_RELEASE_INIT "-Wall -Werror -O3 -s" )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER C:/msys64/clang64/bin/clang.exe)
set(CMAKE_CXX_COMPILER C:/msys64/clang64/bin/clang++.exe)
enable_language(C CXX)

set_property(TARGET PROPERTY C_STANDARD 23)
set_property(TARGET PROPERTY C_STANDARD_REQUIRED TRUE)

# c2 client
add_executable(beacon
  main.c
  include/kb.c
  include/nt.c
  include/http.c
  # include/crypt.c
)
target_include_directories(beacon PUBLIC include)

target_link_libraries(beacon
  PRIVATE
  winhttp     # resolves winhttp
  ws2_32      # resolves winsock
  ntdll       # for nt exports
)

# test module
add_library(test SHARED 
  modules/test.c
)