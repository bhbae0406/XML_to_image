cmake_minimum_required(VERSION 2.8)
project( XML_to_Image )
find_package( OpenCV REQUIRED )
set(CMAKE_BUILD_TYPE "None")
set(CMAKE_CXX_FLAGS "-std=c++11")
add_executable( xmlImage parser.cpp )
target_link_libraries( xmlImage ${OpenCV_LIBS} )
