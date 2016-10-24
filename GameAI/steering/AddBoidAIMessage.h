#ifndef ADD_BOID_AI
#define ADD_BOID_AI

#include "GameMessage.h"

class AddBoidAIMessage :public GameMessage
{
public:
	AddBoidAIMessage();
	~AddBoidAIMessage();

	void process();
};

#endif