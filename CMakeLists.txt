cmake_minimum_required(VERSION 3.10)
project("SkillboxSearchEngine" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(CMAKE_USE_OPENSSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)#true

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# enable_testing()#true
# загрузка с удаленного контента
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# add_executable(SkillboxSearchEngine src/main.cpp src/convjson.cpp src/invertindex.cpp src/server.cpp src/search.cpp src/myexception.cpp src/service.cpp)
add_executable(SkillboxSearchEngine src/main.cpp src/convjson.cpp src/server.cpp src/myexception.cpp)
target_link_libraries(SkillboxSearchEngine PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(SkillboxSearchEngine PUBLIC ${MY_INCLUDE_DIR})


# target_include_directories(SkillboxSearchEngine PUBLIC ${NILS_LIB})


# add_subdirectory(${CMAKE_SOURCE_DIR}/nlohmann_json)#true

# add_subdirectory(src)
# add_subdirectory(tests)#true