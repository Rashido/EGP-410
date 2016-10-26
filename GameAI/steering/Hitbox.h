#ifndef HIT_BOX
#define HIT_BOX

#include "Trackable.h"
#include <memory>

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
	void draw();

	Vector2D getPosition(); //return boxes position, assumes position is center point
	inline float getWidth() { return maxX - minX; };
	inline float getHeight() { return maxY - minY; };

private:
	float minX;
	float minY;
	float maxX;
	float maxY;

	std::shared_ptr<bool> mpShowBoxes;
};

#endif