#include "renderer.h"
#include "VkBootstrap.h"

#include <core/window/window.h>

VkInstance Renderer::_instance;
VkSurfaceKHR Renderer::_surface;
VkPhysicalDevice Renderer::_gpu;
VkDevice Renderer::_device;

void Renderer::Init()
{
    vkb::InstanceBuilder builder;

    auto instanceRet = builder.set_app_name("rendering-exp")
#ifndef NDEBUG
                           .request_validation_layers()
                           .set_debug_callback(
                               [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                  VkDebugUtilsMessageTypeFlagsEXT messageType,
                                  const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                  void *pUserData)
                                   -> VkBool32
                               {
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
#endif
                           .enable_extensions(Window::GetRequiredVulkanExtensions())
                           .require_api_version(VK_MAKE_VERSION(1, 3, 0))
                           .build();

    if (!instanceRet)
    {
        ABORT("Failed to create Vulkan instance");
    }

    vkb::Instance instance = instanceRet.value();

    _instance = instance.instance;

    VkPhysicalDeviceVulkan13Features features13{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
    features13.dynamicRendering = true;
    features13.synchronization2 = true;

    VkPhysicalDeviceVulkan12Features features12{.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
    features12.bufferDeviceAddress = true;
    features12.descriptorIndexing = true;

    vkb::PhysicalDeviceSelector selector{instance};
    auto gpuRet = selector
                      .set_minimum_version(1, 3)
                      .set_required_features_13(features13)
                      .set_required_features_12(features12)
                      .set_surface(Window::CreateVkSurfaceKHR(_instance))
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

    vkb::SwapchainBuilder swapchainBuilder{deviceRet.value()};
    // TODO: keep going
}

void Renderer::Release()
{
    vkDestroyDevice(_device, nullptr);
    vkDestroySurfaceKHR(_instance, _surface, nullptr);
    vkDestroyInstance(_instance, nullptr);
}
