cmake_minimum_required (VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=gnu++17 -static -static-libgcc -static-libstdc++")
project(pagercall)

#includes
include_directories(pagercall PRIVATE
  #WiringPi (automatically included, because system path!)
  # /usr/include

  #Application
  dep
  src
)


add_executable(airsniffer
  src/mx_cc1101.c
  src/airsniffer.c
)


add_executable(pagercall
  dep/argtable3/argtable3.c
  src/mx_cc1101.c
  src/pagercall.c
)


#libraries / dependencies
target_link_libraries(airsniffer PRIVATE
  wiringPi
)
target_link_libraries(pagercall PRIVATE
  m
  wiringPi
)
