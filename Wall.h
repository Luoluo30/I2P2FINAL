#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "Object.h"
#include <allegro5/bitmap.h>
#include <string>

class Wall : public Object
{
public:
	Wall(const Point &p);
	void update();
	void draw();
private:
	ALLEGRO_BITMAP *bitmap;
};

#endif
