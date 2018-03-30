cmake_minimum_required(VERSION 2.8)
project(libfsort)

find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/../include)
link_directories(${CMAKE_SOURCE_DIR}/../lib)

file(GLOB CPP_FILES ./*.cpp)
file(GLOB INCLUDES ./*.h)
set(LIBS caffe glog cblas gflags protobuf m hdf5_hl hdf5 boost_system boost_filesystem boost_thread)

add_library(libfsort STATIC ${CPP_FILES})
add_executable(libfsort ${CPP_FILES} ${INCLUDES})

target_link_libraries(libfsort ${LIBS} ${OpenCV_LIBS})
