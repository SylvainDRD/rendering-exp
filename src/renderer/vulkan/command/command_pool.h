#pragma once
#include <core/utils.h>
#include <vulkan/vulkan.h>
#include <renderer/vulkan/command/command_buffer.h>

class CommandPool {
	NO_CP(CommandPool)

public:
	CommandPool() = default;

	CommandPool(uint32_t queueFamilyIndex);

	CommandPool(CommandPool&& pool) noexcept;

	CommandPool& operator=(CommandPool&& pool) noexcept;

	~CommandPool();

	CommandBuffer GetCommandBuffer(uint64_t frameId) { return _buffer; }

private: 	
	VkCommandPool _pool;

	CommandBuffer _buffer;
};