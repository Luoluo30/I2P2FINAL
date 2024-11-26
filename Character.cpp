#include "Character.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include <stdio.h>
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
    if (DC->key_state[ALLEGRO_KEY_W])
    {
        shape->update_center_y(shape->center_y() - speed);
        state = CharacterState::BACK;
    }
    else if (DC->key_state[ALLEGRO_KEY_A])
    {
        shape->update_center_x(shape->center_x() - speed);
        state = CharacterState::LEFT;
    }
    else if (DC->key_state[ALLEGRO_KEY_S])
    {
        shape->update_center_y(shape->center_y() + speed);
        state = CharacterState::FRONT;
    }
    else if (DC->key_state[ALLEGRO_KEY_D])
    {
        shape->update_center_x(shape->center_x() + speed);
        state = CharacterState::RIGHT;
    }
    else if (DC->key_state[ALLEGRO_KEY_SPACE])
    {
        Character::attack();
    }
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

void Character::attack()
{
    DataCenter *DC = DataCenter::get_instance();
    if (state == CharacterState::FRONT){}
    else if (state == CharacterState::BACK){}
    else if (state == CharacterState::RIGHT){}
    else if (state == CharacterState::LEFT){}
}