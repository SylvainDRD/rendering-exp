#include "window.h"

GLFWwindow *Window::_window;

void Window::Init()
{
    if (glfwInit() != GLFW_TRUE)
    {
        ABORT("GLFW init failed");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    _window = glfwCreateWindow(1280, 720, "Rendering exp", nullptr, nullptr);

    if (_window == nullptr)
    {
        ABORT("Window creation failed")
    }
}

void Window::Release() {
    glfwDestroyWindow(_window);
    _window = nullptr;

    glfwTerminate();
}

void Window::Update()
{
    glfwPollEvents();
}

bool Window::IsClosing()
{
    return glfwWindowShouldClose(_window) == GLFW_TRUE;
}

std::vector<const char *> Window::GetRequiredVulkanExtensions()
{
    uint32_t count;
    const char **exts = glfwGetRequiredInstanceExtensions(&count);

    std::vector<const char *> extensions{count};

    for (int i = 0; i < count; ++i)
    {
        extensions[i] = exts[i];
    }

    return extensions;
}

VkSurfaceKHR Window::CreateVkSurfaceKHR(VkInstance instance)
{
    VkSurfaceKHR surface;
    if (glfwCreateWindowSurface(instance, _window, nullptr, &surface) != VK_SUCCESS)
    {
        ABORT("VkSurfaceKHR creation failed");
    }

    return surface;
}