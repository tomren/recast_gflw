cmake_minimum_required(VERSION 2.8)

# 使用绝对路径
set (CMAKE_USE_RELATIVE_PATHS ON)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
# Windows Visual Studio
if(MSVC)
    # 设置编译的标记位
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif(MSVC)

project(recast_glfw)

# INCLUDE PATH
include_directories(${PROJECT_SOURCE_DIR}/deps)
include_directories(${PROJECT_SOURCE_DIR}/deps/glew/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/glfw/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# SOURCE PATH
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_MAIN)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/framework SRC_FRAMEWORK)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/input SRC_INPUT)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/shader SRC_SHADER)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/texture SRC_TEXTURE)

set (SOURCE_CODE 
    ${SRC_MAIN}
    ${SRC_FRAMEWORK}
    ${SRC_INPUT}
    ${SRC_SHADER}
    ${SRC_TEXTURE}
    )

# LIBORARY
link_directories(${PROJECT_SOURCE_DIR}/deps/glew/lib)
link_directories(${PROJECT_SOURCE_DIR}/deps/glfw/lib)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")

add_executable(recast_glfw  ${SOURCE_CODE})
if(CMAKE_BUILD_TYPE MATCHES "Release")
target_link_libraries(recast_glfw "opengl32" "glew" "glfw3")
else()
target_link_libraries(recast_glfw "opengl32" "glewd" "glfw3d")
endif()