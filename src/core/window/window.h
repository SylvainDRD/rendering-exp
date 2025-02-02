#pragma once
#include <core/utils.h>
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <vector>

class Window
{
    NO_CPMV(Window)

public:
    static void Init();

    static void Release();

    static void Update();

    static void SwapBuffers();

    static bool IsClosing();

    static uint32_t Width();

    static uint32_t Height();

    static std::vector<const char *> GetRequiredVulkanExtensions();

    static VkSurfaceKHR CreateVkSurfaceKHR(VkInstance instance);

private: 
    Window() = default;
    ~Window() = default;

private:
    static GLFWwindow *_window;
};