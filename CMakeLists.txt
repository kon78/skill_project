cmake_minimum_required(VERSION 3.10)
project("SkillboxSearchEngine" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.10)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(CMAKE_USE_OPENSSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# enable_testing()
# add_executable(SkillboxSearchEngine main.cpp convjson.cpp service.cpp maininstr.cpp)

# enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/nlohmann_json)

add_subdirectory(src)
# add_subdirectory(tests)
