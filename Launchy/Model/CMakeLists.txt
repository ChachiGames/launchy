project(Model)


set(target_sources
    model.cpp
)
list(TRANSFORM target_sources PREPEND "src/")


add_library(${PROJECT_NAME} STATIC ${target_sources})
target_include_directories(${PROJECT_NAME} PUBLIC "./include")

#=================================
#              TEST
#=================================

find_package(Catch2 REQUIRED)
add_executable(ModelTests "test/test.cpp")
target_link_libraries(ModelTests PRIVATE Catch2::Catch2WithMain Model)

include(CTest)
include(Catch)
catch_discover_tests(ModelTests)