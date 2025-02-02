#include "texture.h"
#include <renderer/vulkan/renderer.h>

Texture::~Texture()
{
    if (_image != VK_NULL_HANDLE)
    {
        vkDestroyImage(Renderer::Device(), _image, nullptr);
    }
}

Texture::Texture(VkImage image)
{
    _image = image;
}

Texture::Texture(Texture &&texture)
{
    _image = texture._image;
    texture._image = VK_NULL_HANDLE;
}

Texture &Texture::operator=(Texture &&texture)
{
    _image = texture._image;
    texture._image = VK_NULL_HANDLE;
    return *this;
}
