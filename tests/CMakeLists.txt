cmake_minimum_required(VERSION 3.10)

project(SkillboxSearchEngine-tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
# set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# GTest
include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


include_directories(
    ${MY_INCLUDE_DIR}
    ${GTEST_INCLUDE_DIRS}
    # ${MY_INCLUDE_DIR}/nlohmann_json
    )

    set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)#true
    
    set(gtest_disable_pthreads on)
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    
    add_executable(TestSerialization ./multiply_test.cpp
    ../src/service.cpp
    ../src/invertindex.cpp
    ../src/convjson.cpp
    # ../src/multiply.cpp
    # ../src/service.cpp ../src/convjson.cpp
    )#true
    
    target_include_directories(TestSerialization PUBLIC ${NILS_LIB})
    # add_executable(TestSkillboxSearchEngine multiply_test.cpp
    # ../src/multiply.cpp
    # )#true
    # target_link_directories(TestSkillboxSearchEngine PUBLIC ${MY_INCLUDE_DIR})#sobiraetsya
    
    target_link_libraries(TestSerialization ${GTEST_LIBRARIES} PRIVATE GTest::GTest)#true
    target_link_libraries(TestSerialization PRIVATE nlohmann_json::nlohmann_json)
    include(GoogleTest)
    gtest_discover_tests(TestSerialization)
    
    enable_testing()#true
# add_test(Serialization TestSerialization)#true
#собранный тест должен находиться в папке C:\develop\skill_project\build\tests, иначе он не подключается
#тест в файле multiply_test.cpp проходит