project(lazy_rss CXX)

cmake_minimum_required(VERSION 3.0)

find_package(Poco REQUIRED Foundation Net NetSsl)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Os -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Os")

file(GLOB lazy_rss_SRC "src/rss/*.cpp")
add_library(lazy_rss STATIC "${lazy_rss_SRC}")

file(GLOB utils_SRC "src/utils/*.cpp")
add_library(lazy_utils STATIC "${utils_SRC}")

file(GLOB rss_SRC "src/*.cpp")

###########################
# Executable (on by default)
##########################
option(EXEC "Build exectuable" ON)
if (EXEC)
    add_executable(get_rss "${rss_SRC}")
    target_link_libraries(get_rss lazy_utils lazy_rss)
    #Set up Poco lib
    target_link_libraries(get_rss PocoFoundation PocoNet PocoNetSSL PocoXML)
endif()

###########################
# Unit tests
##########################
option(UT "Build tests" OFF)
if (UT)
    set(G_TEST_DIR ${CMAKE_BINARY_DIR}/lib/googletest)

    # Use current master of googletest as 1.8 has bug that prevents compilation with msys2 gcc
    include(ExternalProject)
    ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest

        PREFIX ${G_TEST_DIR}
        INSTALL_COMMAND ""
        # Disable auto-update
        UPDATE_DISCONNECTED 1
    )
    ExternalProject_Get_Property(googletest source_dir binary_dir)

    file(GLOB ut_SRC "test/*.cpp")
    add_executable(ut "${ut_SRC}")

    include_directories(src src/utils src/rss)
    target_link_libraries(ut lazy_utils lazy_rss)
    target_link_libraries(ut PocoFoundation PocoNet PocoNetSSL PocoXML)

    # Add Google Test dependency.
    # Its repo contains sub-projects:
    # - googletest - Source code of gtest.
    # - googlemock - Source code of gmock
    add_dependencies(ut googletest)
    include_directories(${source_dir}/googlemock/include)
    include_directories(${source_dir}/googletest/include)
    # gmock contains gtest so it is enough
    target_link_libraries(ut ${binary_dir}/googlemock/libgmock.a)
    target_link_libraries(ut ${binary_dir}/googlemock/libgmock_main.a)

    enable_testing()
    add_test(NAME    all
             COMMAND ut)
endif()

###########################
# cppcheck
##########################
GET_DIRECTORY_PROPERTY(project_includes INCLUDE_DIRECTORIES)

add_custom_target(
    cppcheck
    COMMAND cppcheck
    --enable=all
    -I ${project_includes}
    ${utils_SRC} ${rss_SRC} ${lazy_rss_SRC}
)
