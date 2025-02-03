#include "queue.h"

Queue Queue::_graphicsQueue;

void Queue::RegisterQueue(QueueType type, VkQueue queue, uint32_t familyIndex)
{
	switch (type)
	{
	case QueueType::GRAPHICS:
		_graphicsQueue = Queue{ queue, familyIndex };
		break;
	case QueueType::TRANSFER:
		break;
	default:
		break;
	}
}

Queue::Queue(VkQueue queue, uint32_t familyIndex)
{
	_queue = queue;
	_familyIndex = familyIndex;
}
