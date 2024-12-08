#include "Character.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include <stdio.h>
#include <string>

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
    shape.reset(new Rectangle{DC->window_width / 2,
                              DC->window_height / 2,
                              DC->window_width / 2 + width,
                              DC->window_height / 2 + height});
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
        next.x + width  , next.y + height 
    };
    for (const auto &wall : DC->walls) {
        if (wall->hitbox->overlap(next_hitbox)) {
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
    Wall* wall;
    if(state == CharacterState::FRONT){
        int space = 0;
        while (true) {
            const Point p(shape->center_x(), shape->center_y() + height + space);
            printf("11111111111111\n");
            if (Character::wall_interact(p) || p.y > 625) {
                break;
            }
            wall = new Wall{p, wall_img_path};
            DC->walls.push_back(wall);
            space += 50;
        }
    }
    else if (state == CharacterState::BACK){
        int space = 50;
        while (true) {
            const Point p(shape->center_x(), shape->center_y() - space);
            printf("^^^^^^^^^^^^^\n");
            if (Character::wall_interact(p) || p.y < 0) {
                break;
            }
            wall = new Wall{p, wall_img_path};
            DC->walls.push_back(wall);
            space += 50;
        }
    }
    else if (state == CharacterState::LEFT){
        int space = 50;
        while (true) {
            const Point p(shape->center_x() - space, shape->center_y());
            printf("<<<<<<<<<<<\n");
            if (Character::wall_interact(p) || p.x < 0) {
                break;
            }
            wall = new Wall{p, wall_img_path};
            DC->walls.push_back(wall);
            space += 50;
        }
    }
    else if (state == CharacterState::RIGHT){
        int space = 0;
        while (true) {
            const Point p(shape->center_x()+ width + space, shape->center_y());
            printf(">>>>>>>>>>>>>>>>>\n");
            if (Character::wall_interact(p) || p.x > 575) {
                break;
            }
            wall = new Wall{p, wall_img_path};
            DC->walls.push_back(wall);
            space += 50;
        }
    }
    else
        return;  

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