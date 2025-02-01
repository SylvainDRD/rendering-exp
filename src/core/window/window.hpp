#include <core/utils.h>
#include <GLFW/glfw3.h>

class Window
{
    NO_CPMV(Window)

public:
    static std::vector<char *> GetVulkanExtensions() const
    {
        uint32_t count;
        const char **exts = glfwGetRequiredInstanceExtensions(&count);

        std::vector<char *> extensions{count};

        for (int i = 0; i < count; ++i)
        {
            extensions[i] = exts[i];
        }

        return extensions;
    }
};