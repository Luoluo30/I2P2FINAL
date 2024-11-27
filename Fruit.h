#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED

#include "Object.h"
#include <allegro5/bitmap.h>
#include <string>

class Fruit : public Object
{
public:
	Fruit(const Point &p);
	void update();
	void draw();
private:
	ALLEGRO_BITMAP *bitmap;
};

#endif
