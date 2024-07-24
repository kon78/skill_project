# GTest
# set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
# FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce8 2e1ff6c30cc3591e5.zip)
#FetchContent_Declare(googletest URL https://github.com/google/googletest.git GIT_TAG release-1.12.1)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# add_executable(multiply_test skill_test.cpp)

add_executable(multiply_test multiply_test.cpp)#true

# add_executable(SkillboxSearchEngine multiply_test.cpp)
# (multiply_test multiply_test.cpp
# add_library(multiply multiply.cpp)
# target_include_directories(multiply PUBLIC ${MY_INCLUDE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/include)#true

target_link_libraries(multiply_test PRIVATE GTest::GTest multiply)#true

add_test(multiply_gtests multiply_test)#true