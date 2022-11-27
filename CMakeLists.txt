cmake_minimum_required(VERSION 3.15)
project(Launchy)

set(CMAKE_CXX_STANDARD 20)

string(REGEX REPLACE "/W[3|4]" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

string(
    APPEND _opts
    "$<IF:$<CXX_COMPILER_ID:MSVC>,"
        "$<$<CONFIG:RELEASE>:/O2>;-WX;,"
        "-Wall;-Wextra;-Werror;"
            "$<$<CONFIG:RELEASE>:-O3>"
            "$<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>"
    ">"
)
add_compile_options("${_opts}")

add_subdirectory(Launchy/Model)
add_subdirectory(Launchy/Controller)
add_subdirectory(Launchy/ConsoleView)
