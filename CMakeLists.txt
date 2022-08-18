cmake_minimum_required(VERSION 3.22)

project(Cross-Platform-Rendering-Engine)

option(BUILD_ASSIMP "Build ASSIMP library" OFF)

SET(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.cpp
)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/*.h
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# GLFW Setup
# ----------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLM Setup
# ---------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
target_link_libraries(${PROJECT_NAME} glm)

# GLEW Setup
# ----------
add_definitions(-DGLEW_STATIC)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)
target_link_libraries(${PROJECT_NAME} libglew_static)

# Glad Setup
# ----------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glad)
target_link_libraries(${PROJECT_NAME} glad)

# ASSIMP Setup
# ------------
if(BUILD_ASSIMP)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp)
    target_link_libraries(${PROJECT_NAME} assimp)
endif()

# Define project properties
# -------------------------
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "RenderingEngine")
