#pragma once
#include "core/utils.h"
#include "vulkan/vulkan.h"
#include <renderer/vulkan/texture/texture.h>
#include <renderer/vulkan/texture/texture_view.h>
#include <vector>

class Renderer
{
    NO_CPMV(Renderer)

public:
    static void Init();

    static void Release();

    static VkDevice Device();

private:
    Renderer() = default;
    ~Renderer() = default;

    static void CreateSwapchain();

private:
    static VkInstance _instance;

    static VkDebugUtilsMessengerEXT _debugMessenger;

    static VkSurfaceKHR _surface;

    static VkPhysicalDevice _gpu;

    static VkDevice _device;

    static VkSwapchainKHR _swapchain;

    static std::vector<Texture> _swapchainImages;

    static std::vector<TextureView> _swapchainImageViews;
};