cmake_minimum_required(VERSION 3.20)
project(Novek)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/main.cpp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
