#include "renderer.hpp"
#include "VkBootstrap.h"

Renderer::Renderer()
{
    vkb::InstanceBuilder builder;

    auto inst_ret = builder.set_app_name("rendering-exp")
                        .request_validation_layers()
                        .use_default_debug_messenger()
                        .build();

    if (!inst_ret)
    {
        ABORT("Failed to create Vulkan instance");
    }

    vkb::Instance instance = inst_ret.value();
    
    vkb::PhysicalDeviceSelector selector{instance};

    // selector.

    // TODO: swapchain
    // vkb::SwapchainBuilder swapchainBuilder{};
}