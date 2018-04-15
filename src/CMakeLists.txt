cmake_minimum_required(VERSION 2.8)
project(libfsort)


set(Caffe_DIR ../caffe/cmake_build)
#set(Caffe_DIR ${CMAKE_SOURCE_DIR}/../caffe/cmake_build)
find_package(Caffe REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${Caffe_DIR}/include)
#add_definitions(${Caffe_DEFINITIONS})
#include_directories(/home/gk1000/dev/libfsort/include /usr/include /usr/local/include)
include_directories(${CMAKE_SOURCE_DIR}/../include /usr/include /usr/local/include)
include_directories(${Caffe_INCLUDE_DIRS})

link_directories(../lib /usr/lib /usr/local/lib)

message(STATUS "src dir: " ${CMAKE_SOURCE_DIR})
message(STATUS "includes: " ${Caffe_INCLUDE_DIRS})
message(STATUS "libs:" ${Caffe_LIBRARIES})

file(GLOB CPP_FILES ./*.cpp)
file(GLOB INCLUDES ./*.h)

set(LIBS bhtsne)
#set(LIBS bhtsne pthread m  boost_system boost_thread glog lmdb cblas hdf5_hl leveldb gflags protobuf hdf5 caffe boost_filesystem caffeproto )
set(BUILD_LIB ON)
set(BUILD_EXECUTABLE ON)
set(OPTIMIZATION_FLAGS OFF)
set(ALL_STATIC OFF)

if(ALL_STATIC)
 SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
 SET(BUILD_SHARED_LIBRARIES OFF)
 SET(CMAKE_EXE_LINKER_FLAGS "-static")
 link_libraries("-static")
endif()


if(BUILD_LIB)
 add_library(fsort STATIC ${CPP_FILES})
 target_link_libraries(fsort ${Caffe_LIBRARIES} ${LIBS} ${OpenCV_LIBS})
endif()

if(BUILD_EXECUTABLE)
 add_executable(fsort_ex ${CPP_FILES} ${INCLUDES})
 target_link_libraries(fsort_ex ${Caffe_LIBRARIES} ${LIBS} ${OpenCV_LIBS} )
endif()
