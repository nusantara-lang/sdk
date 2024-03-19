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
    nusap
    VERSION 1.0.0
    DESCRIPTION "Parser untuk bahasa pemrograman nusantara"
    LANGUAGES CXX
)

file(
	GLOB_RECURSE 
	LIBRARY_SOURCES
	"src/nusap/*.cc"
	"src/nusap/**/*.cc"
)

if(WIN32)
	include_directories("C:/Aerell/AerellDev/nusantara-lang/sdk/nusal/include")
elseif(UNIX)
	include_directories("/home/aerell/project/nusantara-lang/sdk/nusal/include")
endif()
include_directories("include")

set(LIBRARY_NAME nusap)
set(LIBRARY_NAME_OUTPUT nusap)

add_library(
	${LIBRARY_NAME}
	STATIC
	${LIBRARY_SOURCES}
)

if(WIN32)
	target_include_directories(${LIBRARY_NAME} PRIVATE "C:/Aerell/AerellDev/nusantara-lang/sdk/nusal/include")
	target_link_libraries(${LIBRARY_NAME} PRIVATE "C:/Aerell/AerellDev/nusantara-lang/sdk/nusal/build/lib/nusal/libnusal.a")
elseif(UNIX)
	target_include_directories(${LIBRARY_NAME} PRIVATE "/home/aerell/project/nusantara-lang/sdk/nusal/include")
	target_link_libraries(${LIBRARY_NAME} PRIVATE "/home/aerell/project/nusantara-lang/sdk/nusal/build/lib/nusal/libnusal.a")
endif()

set_target_properties(${LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${LIBRARY_NAME_OUTPUT})
set_target_properties(${LIBRARY_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/nusap")

set(EXECUTABLE_NAME nusap_executable)
set(EXECUTABLE_NAME_OUTPUT nusap)

add_executable(
    ${EXECUTABLE_NAME}
    "src/main.cc"
)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${EXECUTABLE_NAME_OUTPUT})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_NAME})

if(${UNIT_TEST} STREQUAL "ON")
	message(STATUS "Unit Test (ON)")
    find_package(GTest QUIET)
    enable_testing()
    file(
        GLOB_RECURSE
        TEST_FILES
        "test/*.cc"
    )
    set(EXECUTABLE_TEST_NAME nusap_test)
    add_executable(
        ${EXECUTABLE_TEST_NAME}
        ${TEST_FILES}
    )
    set_target_properties(${EXECUTABLE_TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    target_link_libraries(
        ${EXECUTABLE_TEST_NAME}
        ${LIBRARY_NAME}
        GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(${EXECUTABLE_TEST_NAME})
else()
	message(STATUS "Unit Test (OFF)")
endif()
