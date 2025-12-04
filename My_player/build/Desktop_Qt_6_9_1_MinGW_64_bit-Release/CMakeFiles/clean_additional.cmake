# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyPlayer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyPlayer_autogen.dir\\ParseCache.txt"
  "MyPlayer_autogen"
  )
endif()
