cmake_minimum_required(VERSION 3.0)
project(soliderfire)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -std=c++11 " )
set(CMAKE_AR "D:\\msys64\\mingw64\\bin\\ar.exe")
set(CMAKE_C_COMPILER "D:\\msys64\\mingw64\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "D:\\msys64\\mingw64\\bin\\g++.exe")
include_directories(${CMAKE_SOURCE_DIR}/include)
set(SRC_CODE "src/Gun.cpp" "src/Solider.cpp" )

add_executable(myCmakeExe src/abstractFactory.cpp)
#add_executable(myCmakeExe main.cpp ${SRC_CODE})
