cmake_minimum_required(VERSION 3.10.2)

project(genNumber)
set(CMAKE_CXX_STANDARD 20)

# Flags
set(GCC_CXX_FLAGS "${GCC_CXX_FLAGS} -lboost_system -lboost_thread -lproj")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fopenmp")


# Boost
find_package(Boost REQUIRED)
set(INC ${INC} ${Boost_INCLUDE_DIR})
set(LIB ${LIB} ${Boost_LIBRARIES})
set(LIB ${LIB} -lboost_system -lboost_thread -lboost_filesystem)
message(STATUS "Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")

add_executable(${PROJECT_NAME} main.cpp)