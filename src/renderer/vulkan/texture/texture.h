#pragma once

#include <core/utils.h>
#include <vulkan/vulkan.h>

class Texture {
    NO_CP(Texture)

public:
    Texture() = delete;

    ~Texture();

    Texture(VkImage image);

    Texture(Texture&& texture);

    Texture& operator=(Texture&& texture);

private:
    VkImage _image;
};