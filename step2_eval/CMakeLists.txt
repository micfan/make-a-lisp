file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)


set(exe step2_eval)
add_executable(${exe}
    ${SRC}
)

target_include_directories(${exe} PUBLIC
        include)
