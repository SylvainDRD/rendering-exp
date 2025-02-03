#include "command_buffer.h"
#include <renderer/vulkan/renderer.h>

CommandBuffer::CommandBuffer(VkCommandPool commandPool)
{
	VkCommandBufferAllocateInfo allocateInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	allocateInfo.commandPool = commandPool;
	allocateInfo.commandBufferCount = 1;
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	vkAllocateCommandBuffers(Renderer::Device(), &allocateInfo, &_buffer);
}

void CommandBuffer::BeginWrite()
{
	VkCommandBufferBeginInfo beginInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkResetCommandBuffer(_buffer, 0);
	vkBeginCommandBuffer(_buffer, &beginInfo);
}

void CommandBuffer::AddBarrier(const VkDependencyInfo* info)
{
	vkCmdPipelineBarrier2(_buffer, info);
}
