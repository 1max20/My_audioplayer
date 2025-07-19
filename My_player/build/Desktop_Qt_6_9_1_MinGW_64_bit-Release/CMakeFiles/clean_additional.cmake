# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\My_player_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\My_player_autogen.dir\\ParseCache.txt"
  "My_player_autogen"
  )
endif()
