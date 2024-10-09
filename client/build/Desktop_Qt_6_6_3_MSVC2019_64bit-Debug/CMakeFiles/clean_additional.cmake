# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\fortuneclient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\fortuneclient_autogen.dir\\ParseCache.txt"
  "fortuneclient_autogen"
  )
endif()
