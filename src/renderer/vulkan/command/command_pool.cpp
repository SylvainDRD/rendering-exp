#include "command_pool.h"
#include <renderer/vulkan/renderer.h>
#include <renderer/vulkan/queue/queue.h>


CommandPool::CommandPool(uint32_t queueFamilyIndex) {
	VkCommandPoolCreateInfo createInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
	createInfo.queueFamilyIndex = queueFamilyIndex;
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	vkCreateCommandPool(Renderer::Device(), &createInfo, nullptr, &_pool);

	_buffer = CommandBuffer{ _pool };
}

CommandPool::CommandPool(CommandPool&& pool) noexcept
{
	_pool = pool._pool;
	_buffer = pool._buffer;

	pool._pool = VK_NULL_HANDLE;
	pool._buffer = {};
}

CommandPool& CommandPool::operator=(CommandPool&& pool) noexcept
{
	_pool = pool._pool;
	_buffer = pool._buffer;

	pool._pool = VK_NULL_HANDLE;
	pool._buffer = {};

	return *this;
}

CommandPool::~CommandPool()
{
	if (_pool != VK_NULL_HANDLE) {
		vkDeviceWaitIdle(Renderer::Device());

		vkDestroyCommandPool(Renderer::Device(), _pool, nullptr);
	}
}
