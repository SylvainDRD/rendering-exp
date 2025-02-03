#pragma once 
#include <core/utils.h>
#include <vulkan/vulkan.h>

class CommandBuffer {
public:
	CommandBuffer() = default;

	CommandBuffer(VkCommandPool commandPool);

	void BeginWrite();

	void AddBarrier(const VkDependencyInfo* info);

private:
	VkCommandBuffer _buffer;
};