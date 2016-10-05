#ifndef WALL_H
#define WALL_H

#include "Trackable.h"
#include "Hitbox.h"

#include <allegro5\allegro_primitives.h>

class Wall : public Trackable
{
public:
	Wall(float x1, float y1, float x2, float y2);
	~Wall();

	inline Hitbox& getHitbox() { return mHitbox; };
	void draw();

private:
	Hitbox mHitbox;

	float minX;
	float minY;
	float maxX;
	float maxY;
};

#endif