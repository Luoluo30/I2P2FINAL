#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"
#include "Wall2.h"

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
    bool ch_interact(const Point &next);
    bool wall_interact(const Point &next);
    void attack(CharacterState state);
    void delete_wall(CharacterState state);
    Point legal_position(Point p);

private:
    CharacterState state = CharacterState::FRONT; // the state of character
    double speed = 5;                   // the move speed of hero
    int width, height;                  // the width and height of the hero image
    std::map<CharacterState, std::string> gifPath;
    std::string wall_img_path = "./assets/image/Wall.jpg";
};
#endif