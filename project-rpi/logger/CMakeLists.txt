cmake_minimum_required(VERSION 3.0)
project(simpleLogger)

set(CMAKE_CXX_STANDARD 11) # Use C++11 or newer

#set(CMAKE_CXX_COMPILER /home/usef/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++)
set(CMAKE_C_COMPILER /home/usef/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /home/usef/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++)

# Specify the path to Boost installation
set(BOOST_ROOT /home/usef/boost_1_76_0)
set(Boost_NO_SYSTEM_PATHS ON) # Prevent system Boost from being used
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)


find_package(Boost 1.76 REQUIRED COMPONENTS log log_setup system thread)
# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})

message(STATUS "** Boost Include: ${Boost_INCLUDE_DIRS}")
message(STATUS "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(STATUS "** Boost Libraries: ${Boost_LIBRARIES}")

# Define simpleLogger library
add_library(simpleLogger simpleLogger.cpp)
# Link Boost libraries and pthread
target_link_libraries(simpleLogger ${Boost_LIBRARIES} pthread)

add_executable(app app.cpp)

target_link_libraries(app simpleLogger)


