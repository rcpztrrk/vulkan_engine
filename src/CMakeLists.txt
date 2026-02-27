file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(VulkanEngine ${SOURCES})

target_include_directories(VulkanEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(VulkanEngine PRIVATE
    Vulkan::Vulkan
    glfw
    spdlog::spdlog_header_only
    glm::glm
    EnTT::EnTT
)
