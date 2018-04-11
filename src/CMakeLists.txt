cmake_minimum_required(VERSION 2.8)
project(libfsort)

find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/../include)
link_directories(${CMAKE_SOURCE_DIR}/../lib)

file(GLOB CPP_FILES ./*.cpp)
file(GLOB INCLUDES ./*.h)
set(LIBS bhtsne caffe glog cblas pthread gflags protobuf m hdf5_hl hdf5 boost_system boost_filesystem boost_thread lmdb leveldb)

set(GXX_FLAGS "-Os -fdata-sections -ffunction-sections")
set(LD_FLAGS "-Wl,--gc-sections -static")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GXX_FLAGS} -static" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LD_FLAGS}" )

add_library(fsort STATIC ${CPP_FILES})
#add_executable(fsort_ex ${CPP_FILES} ${INCLUDES})

target_link_libraries(fsort ${LIBS} ${OpenCV_LIBS})
#target_link_libraries(fsort_ex ${LIBS} ${OpenCV_LIBS})

