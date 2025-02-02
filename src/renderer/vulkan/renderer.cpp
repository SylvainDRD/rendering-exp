#include "renderer.h"
#include "VkBootstrap.h"

#include <core/window/window.h>

VkInstance Renderer::_instance = VK_NULL_HANDLE;
VkDebugUtilsMessengerEXT Renderer::_debugMessenger = VK_NULL_HANDLE;
VkSurfaceKHR Renderer::_surface = VK_NULL_HANDLE;
VkPhysicalDevice Renderer::_gpu = VK_NULL_HANDLE;
VkDevice Renderer::_device = VK_NULL_HANDLE;
VkSwapchainKHR Renderer::_swapchain = VK_NULL_HANDLE;
std::vector<Texture> Renderer::_swapchainImages;
std::vector<TextureView> Renderer::_swapchainImageViews;

void Renderer::Init()
{
    vkb::InstanceBuilder builder;

    auto instanceRet = builder.set_app_name("rendering-exp")
                           .set_debug_callback(
                               [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                                  const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                  void *pUserData)
                                   -> VkBool32
                               {
                                   LOG("test");
                                   if (messageSeverity == VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
                                   {
                                       LOG_WARNING("(Vulkan)" << pCallbackData->pMessage);
                                   }
                                   else if (messageSeverity == VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
                                   {
                                       LOG_ERROR("(Vulkan)" << pCallbackData->pMessage);
                                   }
                                   return VK_FALSE;
                               })
#ifndef NDEBUG
                           .enable_validation_layers(true)
#endif
                           .enable_extensions(Window::GetRequiredVulkanExtensions())
                           .require_api_version(VK_MAKE_VERSION(1, 3, 0))
                           .build();

    if (!instanceRet)
    {
        ABORT("Failed to create Vulkan instance");
    }

    vkb::Instance instance = instanceRet.value();
    _debugMessenger = instance.debug_messenger;

    _instance = instance.instance;

    VkPhysicalDeviceVulkan13Features features13{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
    features13.dynamicRendering = true;
    features13.synchronization2 = true;

    VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
    features12.bufferDeviceAddress = true;
    features12.descriptorIndexing = true;

    _surface = Window::CreateVkSurfaceKHR(_instance);
    vkb::PhysicalDeviceSelector selector{instance};
    auto gpuRet = selector
                      .set_minimum_version(1, 3)
                      .set_required_features_13(features13)
                      .set_required_features_12(features12)
                      .set_surface(_surface)
                      .select();

    if (!gpuRet)
    {
        ABORT("Couldn't select a physical device");
    }

    _gpu = gpuRet.value().physical_device;

    vkb::DeviceBuilder deviceBuilder{gpuRet.value()};

    auto deviceRet = deviceBuilder.build();
    if (!deviceRet)
    {
        ABORT("Couldn't create VkDevice");
    }

    _device = deviceRet.value().device;

    CreateSwapchain();
}

void Renderer::Release()
{
    _swapchainImages.clear();
    _swapchainImageViews.clear();

    vkDestroySwapchainKHR(_device, _swapchain, nullptr);
    vkDestroyDevice(_device, nullptr);
    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkb::destroy_debug_utils_messenger(_instance, _debugMessenger);
    vkDestroyInstance(_instance, nullptr);
}

VkDevice Renderer::Device()
{
    return _device;
}

void Renderer::CreateSwapchain()
{
    if (_swapchain != VK_NULL_HANDLE)
    {
        _swapchainImages.clear();
        _swapchainImageViews.clear();
        vkDestroySwapchainKHR(_device, _swapchain, nullptr);
    }

    vkb::SwapchainBuilder swapchainBuilder{_gpu, _device, _surface};

    auto swapchainRet = swapchainBuilder
                            .set_desired_format(VkSurfaceFormatKHR{.format = VK_FORMAT_B8G8R8A8_UNORM, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR})
                            .set_desired_extent(Window::Width(), Window::Height())
                            .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
                            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
                            .build();
    if (!swapchainRet)
    {
        ABORT("Failed to create the swapchain");
    }

    auto swapchainValue = swapchainRet.value();
    _swapchain = swapchainValue.swapchain;

    std::vector<VkImage> images = swapchainValue.get_images().value();
    std::vector<VkImageView> imageViews = swapchainValue.get_image_views().value();
    for (int i = 0; i < swapchainValue.image_count; ++i)
    {
        _swapchainImages.emplace_back(images[i]);
        _swapchainImageViews.emplace_back(imageViews[i]);
    }
}
