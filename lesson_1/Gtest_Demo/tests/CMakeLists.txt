cmake_minimum_required(VERSION 3.12)

set(Project_Name Gtest_Demo)
set(Test_Name Exampletest)

set(Sources
    test.cc
)

add_executable(${Test_Name} ${Sources})

target_link_libraries(${Test_Name} PRIVATE
    gtest
    gtest_main
    ${Project_Name}
)

add_test(
    NAME ${Test_Name}
    COMMAND ${Test_Name}
)