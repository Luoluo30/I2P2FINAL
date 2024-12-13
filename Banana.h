#ifndef BANANA_H_INCLUDED
#define BANANA_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"

enum class BananaState
{
    APPLE,
    CHARACTERSTATE_MAX
};

class Banana : public Object
{

public:
    Banana(const Point &p);
    void update();
    void draw();
    void destroy();
    Shape *hitbox; 

private:
    int width, height;
    ALLEGRO_BITMAP *bitmap;                 
    
};
#endif