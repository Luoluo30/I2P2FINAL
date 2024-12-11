#ifndef WALL2_H_INCLUDED
#define WALL2_H_INCLUDED

#include "Object.h"
#include <allegro5/bitmap.h>
#include <string>

class Wall2 : public Object
{
public:
    Wall2(const Point &p, const std::string &path);
	void update();
    void draw();
    Shape *hitbox;

private:
    ALLEGRO_BITMAP *bitmap;
    double width;
    double height;     
};

#endif
