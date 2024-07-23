# GTest

include(FetchContent)
# FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce8 2e1ff6c30cc3591e5.zip)
FetchContent_Declare(googletest URL https://github.com/google/googletest.git GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(SkillboxSearchEngine skill_test.cpp)
target_link_libraries(SkillboxSearchEngine
PRIVATE
GTest::GTest
skill_test)

add_test(skill_gtest skill_test)