cmake_minimum_required(VERSION 3.5)
project(bentomark-2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "libs/*.hpp" "libs/*.cpp" )
file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS "test/*.cpp" )
include_directories(${CMAKE_SOURCE_DIR}/libs/)
add_library(CommonLib
    ${LIB_SOURCES}
)
add_library(TestsLib
    ${LIB_SOURCES}
)

function(add_executable_custom _target _sources)
    add_executable(${_target} ${_sources})

    target_link_libraries(${_target} CommonLib)

    add_custom_target(run_${_target}
        COMMAND ./${_target}
        DEPENDS ${_target}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endfunction()

enable_testing()

add_executable_custom(cli src/main.cpp)

add_executable(tests
    ${TESTS_SOURCES}
)
target_link_libraries(tests gtest gtest_main CommonLib TestsLib)
add_custom_target(run_tests
    COMMAND ./tests
    DEPENDS tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

include(GoogleTest)
gtest_discover_tests(tests)
