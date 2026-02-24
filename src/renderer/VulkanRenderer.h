#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <string>

namespace VE {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class VulkanRenderer {
    public:
        VulkanRenderer(GLFWwindow* window);
        ~VulkanRenderer();

        void Init();
        void Shutdown();

    private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createFramebuffers();
        void createGraphicsPipeline();
        void createCommandPool();
        void createCommandBuffers();
        void createSyncObjects();

    public:
        void DrawFrame();

    private:
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

        // Helper functions
        static std::vector<char> readFile(const std::string& filename);
        VkShaderModule createShaderModule(const std::vector<char>& code);
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    private:
        GLFWwindow* m_Window;

        VkInstance m_Instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
        VkSurfaceKHR m_Surface = VK_NULL_HANDLE;

        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice m_Device = VK_NULL_HANDLE;

        VkQueue m_PresentQueue = VK_NULL_HANDLE;
        VkQueue m_GraphicsQueue = VK_NULL_HANDLE;

        VkSwapchainKHR m_SwapChain = VK_NULL_HANDLE;
        std::vector<VkImage> m_SwapChainImages;
        VkFormat m_SwapChainImageFormat;
        VkExtent2D m_SwapChainExtent;
        std::vector<VkImageView> m_SwapChainImageViews;
        
        VkRenderPass m_RenderPass = VK_NULL_HANDLE;
        std::vector<VkFramebuffer> m_SwapChainFramebuffers;

        VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;
        VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;

        VkCommandPool m_CommandPool = VK_NULL_HANDLE;
        std::vector<VkCommandBuffer> m_CommandBuffers;

        std::vector<VkSemaphore> m_ImageAvailableSemaphores;
        std::vector<VkSemaphore> m_RenderFinishedSemaphores;
        std::vector<VkFence> m_InFlightFences;

        uint32_t m_CurrentFrame = 0;
        const int MAX_FRAMES_IN_FLIGHT = 2;

        const std::vector<const char*> m_ValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        
        const std::vector<const char*> m_DeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

#ifdef NDEBUG
        const bool m_EnableValidationLayers = false;
#else
        const bool m_EnableValidationLayers = true;
#endif
    };

}
