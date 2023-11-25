cmake_minimum_required(VERSION 3.5)
project(bentomark-2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bins)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "libs/*.hpp" "libs/*.cpp" )

include_directories(${CMAKE_SOURCE_DIR}/libs/)

add_library(CommonLib
    ${LIB_SOURCES}
)

function(add_executable_custom _target _sources)
    add_executable(${_target} ${_sources})

    target_link_libraries(${_target} CommonLib)

    add_custom_target(run_${_target}
        COMMAND ./${_target}
        DEPENDS ${_target}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bins
    )
endfunction()

add_executable_custom(cli src/main.cpp)
