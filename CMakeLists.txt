cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(launchy CXX)


add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)

set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory(SDL)


add_executable(launchy ${SOURCESS} ${INCLUDES})

target_link_libraries( launchy SDL2main SDL2-static )