#include "texture.h"
#include <renderer/vulkan/renderer.h>
#include <renderer/vulkan/queue/queue.h>

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

Texture::Texture(Texture &&texture) noexcept
{
    _image = texture._image;
    texture._image = VK_NULL_HANDLE;
}

Texture &Texture::operator=(Texture &&texture) noexcept
{
    _image = texture._image;
    texture._image = VK_NULL_HANDLE;
    return *this;
}

void Texture::ClearNoDestroy()
{
    _image = VK_NULL_HANDLE;
}

void Texture::TransitionImageLayout(CommandBuffer commandBuffer, VkImageLayout currentLayout, VkImageLayout newLayout)
{
    VkImageMemoryBarrier2 barrier{ .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2 };

    barrier.srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    barrier.srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT;
    barrier.dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT;
    barrier.dstAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT;

    barrier.oldLayout = currentLayout;
    barrier.newLayout = newLayout;

    VkImageAspectFlags aspectMask = (newLayout == VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;

    VkImageSubresourceRange subImage{};
    subImage.aspectMask = aspectMask;
    subImage.levelCount = VK_REMAINING_MIP_LEVELS;
    subImage.layerCount = VK_REMAINING_ARRAY_LAYERS;

    barrier.subresourceRange = subImage;
    barrier.image = _image;

    VkDependencyInfo info{.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO};
    info.imageMemoryBarrierCount = 1;
    info.pImageMemoryBarriers = &barrier;

    commandBuffer.AddBarrier(&info);
}
