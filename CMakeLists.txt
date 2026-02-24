cmake_minimum_required(VERSION 3.22)
project(VulkanEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan search
find_package(Vulkan REQUIRED)

# Dependencies via vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(shaders)
