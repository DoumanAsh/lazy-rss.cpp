project(lazy_rss CXX)

cmake_minimum_required(VERSION 2.6)

find_package(Poco REQUIRED Foundation Net NetSsl)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Os -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Os")

file(GLOB utils_SRC "src/utils/*.hpp" "src/utils/*.cpp")
add_library(lazy_utils STATIC "${utils_SRC}")

file(GLOB rss_SRC "src/*.hpp" "src/*.cpp")
add_executable(lazy_rss "${rss_SRC}")
target_link_libraries(lazy_rss lazy_utils)

#Set up Poco lib
include_directories("${_Poco_install_prefix}/include")
target_link_libraries(lazy_rss PocoFoundation PocoNet PocoNetSSL)

