cmake_minimum_required(VERSION 2.8)
project(libfsort)
#include(MergeStaticLibs.cmake)
find_package(Caffe REQUIRED)
#find_package(OpenCV REQUIRED)

#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${CMAKE_SOURCE_DIR}/../include)
link_directories(${CMAKE_SOURCE_DIR}/../lib)
#link_libraries("-static")

file(GLOB CPP_FILES ./*.cpp)
file(GLOB INCLUDES ./*.h)
#file(GLOB OPENCV3_LIBS_ ./opencv3/*.a )
set(LIBS pthread m bhtsne boost_system boost_thread glog lmdb cblas hdf5_hl leveldb gflags protobuf hdf5 caffe boost_filesystem caffeproto )

set(BUILD_EX ON)
set(GXX_FLAGS "-Os -fdata-sections -ffunction-sections")
set(LD_FLAGS "-Wl,--gc-sections ")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GXX_FLAGS} " )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LD_FLAGS}" )
#add_definitions(${Caffe_DEFINITIONS})

add_library(fsort STATIC ${CPP_FILES})

if(BUILD_EX)
add_executable(fsort_ex ${CPP_FILES} ${INCLUDES})
target_link_libraries(fsort_ex ${LIBS} )
endif()

target_link_libraries(fsort ${LIBS} )

target_link_libraries(fsort ${Caffe_LIBRARIES} ${LIBS} ${OpenCV_LIBS})
