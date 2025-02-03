#include "texture_view.h"
#include <renderer/vulkan/renderer.h>

TextureView::~TextureView()
{
    if (_view != VK_NULL_HANDLE) {
        vkDestroyImageView(Renderer::Device(), _view, nullptr);
    }
}

TextureView::TextureView(VkImageView view)
{
    _view = view;
}

TextureView::TextureView(TextureView &&view) noexcept
{
    _view = view._view;
    view._view = VK_NULL_HANDLE;
}

TextureView &TextureView::operator=(TextureView &&view) noexcept
{
    _view = view._view;
    view._view = VK_NULL_HANDLE;
    return *this;
}
