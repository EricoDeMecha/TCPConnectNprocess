cmake_minimum_required(VERSION 3.10)
project(Novek)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/main.cpp)

set(BOOST_DEBUG ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system regex REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message("Boost Version 1.65 found")
endif()
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
