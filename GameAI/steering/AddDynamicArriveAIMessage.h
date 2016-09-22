#ifndef ADD_DYNAMIC_ARRIVE_AI
#define ADD_DYNAMIC_ARRIVE_AI

#include "GameMessage.h"
#include "Vector2D.h"

class AddDynamicArriveAIMessage :public GameMessage
{
public:
	AddDynamicArriveAIMessage();
	~AddDynamicArriveAIMessage();

	void process();
};

#endif