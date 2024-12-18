#ifndef WATERMELON_H_INCLUDED
#define WATERMELON_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"

enum class WatermelonState
{
    APPLE,
    CHARACTERSTATE_MAX
};

class Watermelon : public Object
{

public:
    Watermelon(const Point &p);
    void update();
    void draw();
    void destroy();
    Shape *hitbox; 

private:
    int width, height;
    ALLEGRO_BITMAP *bitmap;                 
    
};
#endif