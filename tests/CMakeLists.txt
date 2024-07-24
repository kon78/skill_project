set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# GTest
include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(multiply_test multiply_test.cpp)#true
target_link_libraries(multiply_test PRIVATE GTest::GTest multiply ${MY_INCLUDE_DIR})#true

add_test(multiply_gtests multiply_test)#true