cmake_minimum_required(VERSION 2.8)
project(bhtsne)

file(GLOB CPP_FILES ./*.cpp)

set(GXX_FLAGS "-Os -fdata-sections -ffunction-sections")
#set(LD_FLAGS "-Wl,--gc-sections")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GXX_FLAGS}" )
#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LD_FLAGS}" )

add_library(bhtsne STATIC ${CPP_FILES})




