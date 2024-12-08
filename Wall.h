#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "Object.h"
#include <allegro5/bitmap.h>
#include <string>

class Wall : public Object
{
public:
    Wall(const Point &p, const std::string &path);
	void update();
    void draw();
    Shape *hitbox;   

private:
    ALLEGRO_BITMAP *bitmap;
    double width;
    double height;     
};

#endif
