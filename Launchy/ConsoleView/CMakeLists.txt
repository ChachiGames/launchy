project(ConsoleView)



set(target_sources
    main.cpp
)
list(TRANSFORM target_sources PREPEND "src/")
find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} ${target_sources})


target_link_libraries(${PROJECT_NAME} PRIVATE Controller fmt::fmt)

#=================================
#              TEST
#=================================

find_package(Catch2 REQUIRED)
add_executable(ConsoleViewTests "test/test.cpp")
target_link_libraries(ConsoleViewTests PRIVATE Catch2::Catch2WithMain Model)

include(CTest)
include(Catch)
catch_discover_tests(ConsoleViewTests)