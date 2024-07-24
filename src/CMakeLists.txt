cmake_minimum_required(VERSION 3.10)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_executable(SkillboxSearchEngine main.cpp convjson.cpp service.cpp maininstr.cpp)

target_include_directories(SkillboxSearchEngine PUBLIC ${MY_INCLUDE_DIR})

target_include_directories(SkillboxSearchEngine PUBLIC ${NILS_LIB})

target_link_libraries(SkillboxSearchEngine PRIVATE nlohmann_json::nlohmann_json)

add_library(multiply multiply.cpp)
target_include_directories(multiply PUBLIC ${MY_INCLUDE_DIR})
