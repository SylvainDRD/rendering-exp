#pragma once
#include <core/utils.h>
#include <vulkan/vulkan.h>

class Texture {
	NO_CP(Texture)

public:
	Texture() = delete;

	~Texture();

	Texture(VkImage image);

	Texture(Texture&& texture) noexcept;

	Texture& operator=(Texture&& texture) noexcept;

	void ClearNoDestroy();

	void TransitionImageLayout(CommandBuffer commandBuffer, VkImageLayout currentLayout, VkImageLayout newLayout);

private:
	VkImage _image;
};