cmake_minimum_required(VERSION 3.20)
project(Novek)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/main.cpp)
# Boost Asio for networking
set(BOOST_DEBUG ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system program_options regex REQUIRED)
if(Boost_FOUND)
    message("${Boost_VERSION_STRING} Boost found")
    include_directories(${Boost_INCLUDE_DIR})
endif()

# zlib for string decompression
set(ZLIB_ROOT  /usr/local/zlib)
set(ZLIB_INCLUDE_DIRS /usr/local/zlib/include)
set(ZLIB_LIBRARIES  /usr/local/zlib/lib)
find_package(ZLIB)
If(ZLIB_FOUND)
    message(${ZLIB_LIBRARIES})
    message("${ZLIB_VERSION_STRING} ZLIB found")
    include_directories(${ZLIB_INCLUDE_DIRS})
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${ZLIB_LIBRARIES} ${Boost_LIBRARIES})
