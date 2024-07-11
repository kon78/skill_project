cmake_minimum_required(VERSION 3.10)
project("SkillboxSearchEngine" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/nlohmann_json)
add_subdirectory(src)
