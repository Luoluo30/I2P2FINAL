#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"

enum class FruitState
{
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    CHARACTERSTATE_MAX
};

class Fruit : public Object
{

public:
    void init();
    void update();
    void draw();
    

private:
    FruitState state = FruitState::FRONT; 
    int width, height;                 
    std::map<FruitState, std::string> gifPath;
    
};
#endif
