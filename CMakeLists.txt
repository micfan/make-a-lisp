cmake_minimum_required (VERSION 3.12)

project(mal-cpp)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    add_compile_options(-fcompare-debug)
endif ()

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
# add_subdirectory(step1_read_print)

