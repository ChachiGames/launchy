project(Controller)


set(target_sources
    controller.cpp
)
list(TRANSFORM target_sources PREPEND "src/")

add_library(${PROJECT_NAME} STATIC ${target_sources} "include/controller.hpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_link_libraries(${PROJECT_NAME} PUBLIC Model)

#=================================
#              TEST
#=================================

find_package(Catch2 REQUIRED)
add_executable(ControllerTests "test/test.cpp")
target_link_libraries(ControllerTests PRIVATE Catch2::Catch2WithMain Model)

include(CTest)
include(Catch)
catch_discover_tests(ControllerTests)