#include "core/utils.h"
#include "vulkan/vulkan.h"

class Renderer {
    NO_CPMV(Renderer)

public: 
    Renderer();

private:
    VkInstance _instance;
};