#pragma once
#include <core/utils.h>
#include <vulkan/vulkan.h>

class TextureView
{
    NO_CP(TextureView)

public:
    TextureView() = delete;

    ~TextureView();

    TextureView(VkImageView view);

    TextureView(TextureView&& view);

    TextureView& operator=(TextureView&& view);

private:
    VkImageView _view;
};