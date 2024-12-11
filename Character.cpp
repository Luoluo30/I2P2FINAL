#include "Character.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include <stdio.h>
#include <string>
#include "Utils.h"

namespace CharacterSetting
{
    static constexpr char gif_root_path[50] = "./assets/gif/Hero";
    static constexpr char gif_postfix[][10] = {
        "left",
        "right",
        "front",
        "back",
    };
}

void Character::init()
{
    for (size_t type = 0; type < static_cast<size_t>(CharacterState::CHARACTERSTATE_MAX); ++type)
    {
        char buffer[50];
        sprintf(
            buffer, "%s/dragonite_%s.gif",
            CharacterSetting::gif_root_path,
            CharacterSetting::gif_postfix[static_cast<int>(type)]);
        gifPath[static_cast<CharacterState>(type)] = std::string{buffer};
    }
    DataCenter *DC = DataCenter::get_instance();
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    width = gif->width;
    height = gif->height;
    shape.reset(new Rectangle{375,
                              350,
                              375 + width,
                              350 + height});
}

void Character::update()
{
    DataCenter *DC = DataCenter::get_instance();
    Point original{shape->center_x(), shape->center_y()};
    Point next = original;
    if (DC->key_state[ALLEGRO_KEY_W])
    {
        next.y -= speed;
        //shape->update_center_y(shape->center_y() - speed);
        state = CharacterState::BACK;
    }
    else if (DC->key_state[ALLEGRO_KEY_A])
    {
        next.x -= speed;
        //shape->update_center_x(shape->center_x() - speed);
        state = CharacterState::LEFT;
    }
    else if (DC->key_state[ALLEGRO_KEY_S])
    {
        next.y += speed;
        //shape->update_center_y(shape->center_y() + speed);
        state = CharacterState::FRONT;
    }
    else if (DC->key_state[ALLEGRO_KEY_D])
    {
        next.x += speed;
        //shape->update_center_x(shape->center_x() + speed);
        state = CharacterState::RIGHT;
    }
    else if (DC->key_state[ALLEGRO_KEY_X])
    {
        Character::delete_wall(state);
    }
    else if (DC->key_state[ALLEGRO_KEY_SPACE])
    {
        Character::attack(state);
    }
    if(!Character::ch_interact(next)){
        shape->update_center_x(next.x);
        shape->update_center_y(next.y);
    }
}

bool Character::ch_interact(const Point &next){
    DataCenter *DC = DataCenter::get_instance();
    Rectangle next_hitbox{
        next.x   , next.y,
        next.x + 48  , next.y + 50
    };
    for (const auto &wall : DC->walls) {
        if (wall->hitbox->overlap(next_hitbox)) {
            return true;
        }
    }
    for (const auto &wall2 : DC->walls2) {
        if (wall2->hitbox->overlap(next_hitbox)) {
            return true;
        }
    }
    return false; 
}



void Character::draw()
{
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
    algif_draw_gif(gif,
                   shape->center_x() - width / 2,
                   shape->center_y() - height / 2,
                   0);
}



void Character::attack(CharacterState state)
{
    DataCenter* DC = DataCenter::get_instance();
    Point p;

    if (state == CharacterState::FRONT) {
        p = Point(shape->center_x(), shape->center_y() + 48);
    } else if (state == CharacterState::BACK) {
        p = Point(shape->center_x(), shape->center_y() - 48);
    } else if (state == CharacterState::LEFT) {
        p = Point(shape->center_x() - 50, shape->center_y());
    } else if (state == CharacterState::RIGHT) {
        p = Point(shape->center_x() + 50, shape->center_y());
    } else {
        return;
    }
    if(!wall_interact(p)){
        Wall *wall = new Wall{legal_position(p), wall_img_path};
        DC->walls.push_back(wall);
    }
}


bool Character::wall_interact(const Point &next){
    DataCenter *DC = DataCenter::get_instance();
    Rectangle next_hitbox{
        next.x   , next.y,
        next.x + 50  , next.y + 48
    };
    for (const auto &wall : DC->walls) {
        if (wall->hitbox->overlap(next_hitbox)) {
            return true;
        }
    }
    return false; 
}

void Character::delete_wall(CharacterState state)
{
    DataCenter* DC = DataCenter::get_instance();
    Point next;
    if (state == CharacterState::FRONT) {
        next = Point(shape->center_x(), shape->center_y() + height);
    } 
    else if (state == CharacterState::BACK) {
        next = Point(shape->center_x(), shape->center_y() - 50);
    }
    else if (state == CharacterState::LEFT) {
        next = Point(shape->center_x() - 50, shape->center_y());
    } else if (state == CharacterState::RIGHT) {
        next = Point(shape->center_x() + width, shape->center_y());
    } else {
        return;
    }

    for (auto it = DC->walls.begin(); it != DC->walls.end(); ) {
    Wall* w = *it;
    if (w->hitbox->overlap(Rectangle{next.x, next.y, next.x + 50, next.y + 48})) {     
        it = DC->walls.erase(it); 
        //debug_log("Wall at (%lf, %lf) deleted.\n", next.x, next.y);
        return;
    } else {
        ++it; 
    }
}
    //debug_log("No wall found to delete at the targeted position.\n");
}

Point Character::legal_position(Point p)
{
    double adjusted_x = (static_cast<int>(p.x) / 100) * 100 + ((static_cast<int>(p.x) % 100 <= 50) ? 25 : 75);
    double adjusted_y = (static_cast<int>(p.y) / 100) * 100 + ((static_cast<int>(p.y) % 100 <= 50) ? 25 : 75);
    return Point(adjusted_x, adjusted_y);
}