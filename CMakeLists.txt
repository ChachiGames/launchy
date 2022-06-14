cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)
project(launchy VERSION "0.0.4" )

configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/src/config.h)

add_subdirectory(src)
add_subdirectory(tests)

# Adding SDL
set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory(lib/SDL)
add_subdirectory(lib/SDL_image)
add_subdirectory(lib/SDL_ttf)

# Adding LibCURL
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )
set( CURL_USE_OPENSSL ON CACHE BOOL "" FORCE )
set( CURL_STATIC_CRT OFF CACHE BOOL "" FORCE )
add_subdirectory(lib/CURL)
include_directories( ${CURL_INCLUDE_DIRS} )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
add_executable(launchy ${SOURCESS})

target_include_directories(launchy PRIVATE ${CMAKE_SOURCE_DIR}/src/)
target_link_libraries( launchy SDL2main SDL2-static SDL2_image SDL2_ttf libcurl)
target_link_libraries( launchy ${CURL_LIBRARIES} )


set_property(TARGET launchy PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/$<CONFIG>/")

add_custom_command(
        TARGET launchy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/dependencies/cacert.pem
                ${CMAKE_SOURCE_DIR}/build/$<CONFIG>/cacert.pem)


#Adding patcher project
set(launchyOutput "${CMAKE_SOURCE_DIR}/build/$<CONFIG>/")

add_executable(patcher src/patcher.cpp)
set(RUNTIME_OUTPUT_DIRECTORY ${launchyOutput})
