#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include <string>
#include <map>
#include "Object.h"
#include "Wall.h"
#include "Wall2.h"
#include "Fruit.h"
#include "Banana.h"
#include "Player.h"
#include "Watermelon.h"

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
    bool wall2_interact(const Point &next);
    void attack(CharacterState state);
    void delete_wall(CharacterState state);
    Point legal_position(Point p);
    double speed = 2;                   // the move speed of hero
    bool invincible;          
    double invincible_timer;   

private:
    CharacterState state = CharacterState::FRONT; // the state of character
    int width, height;                  // the width and height of the hero image
    std::map<CharacterState, std::string> gifPath;
    std::string wall_img_path = "./assets/image/Wall.jpg";
};
#endif