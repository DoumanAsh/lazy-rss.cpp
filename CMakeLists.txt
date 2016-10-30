project(lazy_rss CXX)

cmake_minimum_required(VERSION 3.0)

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

option(test "Build tests" OFF)

if (test)
    set(G_TEST_DIR ${CMAKE_BINARY_DIR}/lib/googletest)

    # Use current master of googletest as 1.8 has bug that prevents compilation with msys2 gcc
    include(ExternalProject)
    ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest

        PREFIX ${G_TEST_DIR}
        INSTALL_COMMAND ""
    )
    ExternalProject_Get_Property(googletest source_dir binary_dir)

    add_executable(FirstTest test/test.cpp)

    # Add Google Test dependency.
    # Its repo contains sub-projects:
    # - googletest - Source code of gtest.
    # - googlemock - Source code of gmock
    add_dependencies(FirstTest googletest)
    include_directories(${source_dir}/googlemock/include)
    include_directories(${source_dir}/googletest/include)
    # gmock contains gtest so it is enough
    target_link_libraries(FirstTest ${binary_dir}/googlemock/libgmock.a)

    enable_testing()
    add_test(NAME    all
             COMMAND FirstTest)
endif()
