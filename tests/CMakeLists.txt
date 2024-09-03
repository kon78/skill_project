cmake_minimum_required(VERSION 3.16)
project(MultiplyTest LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(JSON_BuildTests OFF CACHE INTERNAL "")#модульные тесты сборки
# set(CMAKE_USE_OPENSSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)#true

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(multiply_test multiply_test.cpp
#  ../src/service.cpp
#   ../src/appparam.cpp
  )



target_link_libraries(multiply_test
 PRIVATE
  GTest::GTest
  nlohmann_json::nlohmann_json
  multiply)

  enable_testing()
add_test(multiply_gtests multiply_test)
