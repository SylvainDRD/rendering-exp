#pragma once
#include <core/utils.h>
#include <vulkan/vulkan.h>
#include <vector>

enum class QueueType : uint8_t {
	GRAPHICS = 0,
	TRANSFER = 1
};

class Queue {
public:
	Queue() = default;

	static void RegisterQueue(QueueType type, VkQueue queue, uint32_t familyIndex);

	static Queue& GetGraphicsQueue() { return _graphicsQueue; }

	VkQueue GetVkQueue() const { return _queue; }

	uint32_t GetFamilyIndex() const { return _familyIndex; }

private:
	Queue(VkQueue queue, uint32_t familyIndex);

private:
	static Queue _graphicsQueue;

	VkQueue _queue; 
	uint32_t _familyIndex;
};