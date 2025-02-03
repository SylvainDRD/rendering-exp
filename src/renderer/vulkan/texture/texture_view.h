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

    TextureView(TextureView&& view) noexcept;

    TextureView& operator=(TextureView&& view) noexcept;

private:
    VkImageView _view;
};