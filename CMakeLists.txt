cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(launchy CXX)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)

# Adding SDL
set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory(lib/SDL)

# Adding LibCURL

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )
set( CURL_USE_OPENSSL ON CACHE BOOL "" FORCE )
set( CURL_STATIC_CRT ON CACHE BOOL "" FORCE )
add_subdirectory(lib/CURL)
include_directories( ${CURL_INCLUDE_DIRS} )



add_executable(launchy ${SOURCESS} ${INCLUDES})

target_link_libraries( launchy SDL2main SDL2-static libcurl)
target_link_libraries( launchy ${CURL_LIBRARIES} )


set_property(TARGET launchy PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/$<CONFIG>/")