#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"

enum class CharacterState
{
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    CHARACTERSTATE_MAX
};


class Character : public Object
{

public:
    void init();
    void update();
    void draw();
    Wall *attack(CharacterState state);

private:
    CharacterState state = CharacterState::FRONT; // the state of character
    double speed = 5;                   // the move speed of hero
    int width, height;                  // the width and height of the hero image
    std::map<CharacterState, std::string> gifPath;
    std::string wall_img_path = "./assets/image/Wall.jpg";
};
#endif