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

    static bool IsClosing();

    static std::vector<const char *> GetRequiredVulkanExtensions();

    static VkSurfaceKHR CreateVkSurfaceKHR(VkInstance instance);

private: 
    Window() = default;
    ~Window() = default;

private:
    static GLFWwindow *_window;
};