#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"

enum class FruitState
{
    APPLE,
    CHARACTERSTATE_MAX
};

class Fruit : public Object
{

public:
    Fruit(const Point &p);
    void update();
    void draw();
    void destroy();
    Shape *hitbox; 

private:
    int width, height;
    ALLEGRO_BITMAP *bitmap;                 
    
};
#endif