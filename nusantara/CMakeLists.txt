cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(UNIT_TEST OFF)

if(WIN32)
    message(STATUS "Platform (Windows)")
    set(CMAKE_CXX_COMPILER "clang++")
    set(CMAKE_CXX_FLAGS "-Ofast -ffast-math -flto -march=native -mtune=native -fstack-protector -msse2 -mavx -g -Wall -Wextra")
    set(CMAKE_LINKER "lld")
elseif(UNIX)
    message(STATUS "Platform (Linux)")
    set(CMAKE_CXX_COMPILER "clang++-17")
    set(CMAKE_CXX_FLAGS "-Ofast -ffast-math -flto -march=native -mtune=native -fstack-protector -g -fPIE -Wall -Wextra")
    set(CMAKE_LINKER "lld-17")
endif()

project(
    nusantara
    VERSION 1.0.0
    DESCRIPTION "Runtime untuk bahasa pemrograman nusantara"
    LANGUAGES CXX
)

file(
	GLOB_RECURSE 
	SOURCE_FILES
	"src/*.cc"
	"src/**/*.cc"
)

include_directories(include)

add_executable(
    nusantara
    ${SOURCE_FILES}
)

set_target_properties(nusantara PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(${UNIT_TEST} STREQUAL "ON")
	message(STATUS "Unit Test (ON)")
    find_package(GTest QUIET)
    enable_testing()
    file(
        GLOB_RECURSE
        TEST_FILES
        "test/*.cc"
    )
    add_executable(
        nusantara_test
        ${TEST_FILES}
    )
    set_target_properties(nusantara_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_link_libraries(
        nusantara_test
        ${LIBRARY_NAME}
        GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(nusantara_test)

    install(
        TARGETS nusantara_test
        DESTINATION bin
    )
else()
	message(STATUS "Unit Test (OFF)")
endif()

install(
    TARGETS nusantara
    DESTINATION bin
)