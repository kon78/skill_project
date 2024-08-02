cmake_minimum_required(VERSION 3.10)
project("SkillboxSearchEngine" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(CMAKE_USE_OPENSSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)#true

# enable_testing()#true

add_executable(SkillboxSearchEngine src/main.cpp src/convjson.cpp src/service.cpp src/maininstr.cpp src/invertindex.cpp)

target_include_directories(SkillboxSearchEngine PUBLIC ${MY_INCLUDE_DIR})

target_include_directories(SkillboxSearchEngine PUBLIC ${NILS_LIB})

target_link_libraries(SkillboxSearchEngine PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(${CMAKE_SOURCE_DIR}/nlohmann_json)#true

# add_subdirectory(src)
add_subdirectory(tests)#true