#include "core/utils.h"
#include "vulkan/vulkan.h"

class Renderer
{
    NO_CPMV(Renderer)

public:
    static void Init();

    static void Release();

private:
    Renderer() = default;
    ~Renderer() = default;

private:
    static VkInstance _instance;

    static VkSurfaceKHR _surface;

    static VkPhysicalDevice _gpu;

    static VkDevice _device;
};