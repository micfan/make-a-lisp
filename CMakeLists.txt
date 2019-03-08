cmake_minimum_required (VERSION 3.12)

project(mal-cpp)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fcompare-debug)
endif ()

# Git Submodule init
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" OFF)

    set(LINENOISE_DIR third_party/linenoise)
    set(SPDLOG_DIR third_party/spdlog)
    IF(EXISTS ${SPDLOG_DIR} AND IS_DIRECTORY ${SPDLOG_DIR})
        message(STATUS "Submodule: ${SPDLOG_DIR} has already inited before")
    else()
        message(STATUS "Performing Git Submodule init & update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
else()
     message(FATAL_ERROR "Git NOT FOUND, can not init submodules!")
endif()

add_subdirectory(third_party/linenoise)
add_subdirectory(third_party/spdlog)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
#find_package(spdlog CONFIG REQUIRED)
link_libraries(
        spdlog::spdlog
        linenoise
)

message(STATUS "Got ${LINENOISE_INCLUDE_DIR}")
include_directories(
        ${LINENOISE_INCLUDE_DIR}
)

message(STATUS ${LINENOISE_INCLUDE_DIR})


add_subdirectory(step0_repl)
add_subdirectory(step1_read_print)

