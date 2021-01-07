cmake_minimum_required(VERSION 3.17)
project(sdtp)
set(CMAKE_CXX_STANDARD 11)
# 项目编译
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE  ProjectSrc ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(ProBuildSrc ${ProjectSrc} )

add_executable(${PROJECT_NAME} ${ProBuildSrc})
set_target_properties(${ProjectName} PROPERTIES  EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


# 单元测试编译
set(TestProjectName Test${PROJECT_NAME})
include_directories(
        ${PROJECT_SOURCE_DIR}/deps/Catch2/include
        ${PROJECT_SOURCE_DIR}/test/include)
file(GLOB_RECURSE ThirdPartySrc "")
file(GLOB_RECURSE ProjectSrc ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM ProjectSrc ${PROJECT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE TestSrc "${PROJECT_SOURCE_DIR}/test/src/*.cpp")

set(TestBuildSrc ${ThirdPartySrc} ${ProjectSrc} ${TestSrc})
add_executable(${TestProjectName} ${TestBuildSrc})
set_target_properties(${TestProjectName} PROPERTIES  EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
