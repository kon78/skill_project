cmake_minimum_required(VERSION 3.10)

set(BUILD_CPRTESTS OFF)
set(CMAKE_USE_OPENSSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(JSON_BuildTests OFF CACHE INTERNAL "")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(NLOHMANN_LIB "C:/develop/nlohmann_json")
set(NILS_LIB ${CMAKE_SOURCE_DIR}/nlohmann_json/include)
include(FetchContent)
FetchContent_Declare(json URL ${NLOHMANN_LIB})
FetchContent_MakeAvailable(json)

set(CMAKE_PREFIX_PATH "C:\\Qt_mingw\\6.8.0\\mingw_64\\lib\\cmake")
# C:\Qt_mingw\6.8.0\mingw_64

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(SkillboxSearchEngine main.cpp convjson.cpp service.cpp)
target_include_directories(SkillboxSearchEngine PUBLIC ${MY_INCLUDE_DIR})

target_include_directories(SkillboxSearchEngine PUBLIC ${NLOHMANN_LIB})

target_link_libraries(SkillboxSearchEngine PRIVATE nlohmann_json::nlohmann_json Qt6::Core ${CIMG_INCLUDE_DIR})
