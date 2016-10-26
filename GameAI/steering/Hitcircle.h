#ifndef HIT_CIRCLE
#define HIT_CIRCLE

#include "Trackable.h"
#include "Vector2D.h"

class Hitbox;

class Hitcircle :public Trackable
{
public:
	Hitcircle();
	Hitcircle(Vector2D position, float radius);
	~Hitcircle() {};

	void update(float deltaX, float deltaY);
		
	bool checkCollision(Hitbox& otherBox);
private:
	Vector2D mPos;
	float mRadius;
};

#endif