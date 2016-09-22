#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "Trackable.h"
#include <allegro5\allegro.h>

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();

	void init();
	void update();
	void cleanUp();

private:
	//allegro input
	ALLEGRO_EVENT mEvent;
	ALLEGRO_EVENT_QUEUE* mpEventQueue;
};

#endif