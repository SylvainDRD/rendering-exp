#include "texture_view.h"

TextureView::~TextureView()
{
}

TextureView::TextureView(VkImageView view)
{
    _view = view;
}

TextureView::TextureView(TextureView &&view)
{
    _view = view._view;
    view._view = VK_NULL_HANDLE;
}

TextureView &TextureView::operator=(TextureView &&view)
{
    _view = view._view;
    view._view = VK_NULL_HANDLE;
    return *this;
}
