#include "window.h"

GLFWwindow *Window::_window;

void Window::Init()
{
    if (!glfwInit())
    {
        ABORT("GLFW init failed");
    }

    glfwSwapInterval(1);

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

void Window::SwapBuffers()
{
    glfwSwapBuffers(_window);
}

bool Window::IsClosing()
{
    return glfwWindowShouldClose(_window) == GLFW_TRUE;
}

uint32_t Window::Width()
{
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return width;
}

uint32_t Window::Height()
{
    int width, height;
    glfwGetWindowSize(_window, &width, &height);
    return height;
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