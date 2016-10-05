#ifndef HIT_BOX
#define HIT_BOX

#include "Trackable.h"

class Vector2D;

class Hitbox : public Trackable
{
public:
	Hitbox();
	Hitbox(Vector2D position, float width, float height);
	Hitbox(float x1, float y1, float x2, float y2);
	~Hitbox();

	bool checkCollision(Hitbox& otherBox);
	void update(float deltaX, float deltaY);

private:
	float minX;
	float minY;
	float maxX;
	float maxY;
};

#endif