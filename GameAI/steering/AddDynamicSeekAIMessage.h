#ifndef ADD_DYNAMIC_SEEK_AI
#define ADD_DYNAMIC_SEEK_AI

#include "GameMessage.h"
#include "Vector2D.h"

class AddDynamicSeekAIMessage :public GameMessage
{
public:
	AddDynamicSeekAIMessage();
	~AddDynamicSeekAIMessage();

	void process();
};

#endif