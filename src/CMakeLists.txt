cmake_minimum_required(VERSION 3.10)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(CMAKE_USE_OPENSSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(SkillboxSearchEngine main.cpp convjson.cpp service.cpp maininstr.cpp)
target_include_directories(SkillboxSearchEngine PUBLIC ${MY_INCLUDE_DIR})

target_include_directories(SkillboxSearchEngine PUBLIC ${NILS_LIB})

target_link_libraries(SkillboxSearchEngine PRIVATE nlohmann_json::nlohmann_json)
