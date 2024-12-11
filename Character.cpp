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
    width = 43;
    height = 43;
    shape.reset(new Rectangle{300,
                              300,
                              300 + width,
                              300 + height});
}

// void Character::update()
// {
//     static double last_input_time = 0; // 上一次按键检测的时间
//     double current_time = al_get_time(); // 获取当前时间

//     // 检查是否超过 0.1 秒（100 毫秒）的等待时间
//     if (current_time - last_input_time < 0.18) {
//         return; // 如果不足 0.1 秒，则直接返回，不处理按键
//     }
//     static Point target = {shape->center_x(), shape->center_y()}; // 目标位置
//     DataCenter *DC = DataCenter::get_instance();
//     Point original{shape->center_x(), shape->center_y()};
//     Point next = original;
//     if (DC->key_state[ALLEGRO_KEY_W])
//     {
//         target = Point(original.x, original.y - 50);
//         //shape->update_center_y(shape->center_y() - speed);
//         state = CharacterState::BACK;
//         last_input_time = current_time;
//         if(!Character::ch_interact(target)){
//             while(next.y>=target.y){
//                 double start_time = al_get_time();
//                 shape->update_center_y(next.y);
//                 al_flip_display();
//                 next.y -= speed;
//                 while (al_get_time() - start_time < 0.005);
//             } 
//             next.y = target.y;
//             shape->update_center_y(next.y);
//         } 
//     }
//     else if (DC->key_state[ALLEGRO_KEY_A])
//     {
//         target = Point(original.x - 50, original.y);
//         //shape->update_center_x(shape->center_x() - speed);
//         state = CharacterState::LEFT;
//         last_input_time = current_time;
//         if(!Character::ch_interact(target)){
//             while(next.x>=target.x){
//                 double start_time = al_get_time();
//                 shape->update_center_x(next.x);
//                 al_flip_display();
//                 next.x -= speed;
//                 while (al_get_time() - start_time < 0.005);
//             }
//             next.x = target.x;
//             shape->update_center_x(next.x);
//         }
//     }
//     else if (DC->key_state[ALLEGRO_KEY_S])
//     {
//         target = Point(original.x, original.y + 50);
//         //shape->update_center_y(shape->center_y() + speed);
//         state = CharacterState::FRONT;
//         last_input_time = current_time;
//         if(!Character::ch_interact(target)){
//             while(next.y<=target.y){
//                 double start_time = al_get_time();
//                 shape->update_center_y(next.y);
//                 al_flip_display();
//                 next.y += speed;
//                 while (al_get_time() - start_time < 0.005);
//             }
//             next.y = target.y;
//             shape->update_center_y(next.y);
//         } 
//     }
//     else if (DC->key_state[ALLEGRO_KEY_D])
//     {
//         target = Point(original.x + 50, original.y);
//         //shape->update_center_x(shape->center_x() + speed);
//         state = CharacterState::RIGHT;
//         last_input_time = current_time;
//         if(!Character::ch_interact(target)){
//             while(next.x<=target.x){
//                 double start_time = al_get_time();
//                 shape->update_center_x(next.x);
//                 al_flip_display();
//                 next.x += speed;
//                 while (al_get_time() - start_time < 0.005);
//             }
//             next.x = target.x;
//             shape->update_center_x(next.x);
//         }

//     }
//     else if (DC->key_state[ALLEGRO_KEY_X])
//     {
//         Character::delete_wall(state);
//         last_input_time = current_time;
//     }
//     else if (DC->key_state[ALLEGRO_KEY_SPACE])
//     {
//         Character::attack(state);
//         last_input_time = current_time;
//     }

// }
void Character::update()
{
    static Point target = {shape->center_x(), shape->center_y()}; 
    static bool is_moving = false; 

    DataCenter *DC = DataCenter::get_instance();
    Point next = {shape->center_x(), shape->center_y()};

    if (!is_moving) {
        if (DC->key_state[ALLEGRO_KEY_W]) {
            target = Point(next.x, next.y - 50);
            state = CharacterState::BACK;
            is_moving = true; 
        } else if (DC->key_state[ALLEGRO_KEY_A]) {
            target = Point(next.x - 50, next.y);
            state = CharacterState::LEFT;
            is_moving = true; 
        } else if (DC->key_state[ALLEGRO_KEY_S]) {
            target = Point(next.x, next.y + 50);
            state = CharacterState::FRONT;
            is_moving = true;
        } else if (DC->key_state[ALLEGRO_KEY_D]) {
            target = Point(next.x + 50, next.y);
            state = CharacterState::RIGHT;
            is_moving = true; 
        } else if (DC->key_state[ALLEGRO_KEY_X]) {
            Character::delete_wall(state);
        } else if (DC->key_state[ALLEGRO_KEY_SPACE]) {
            Character::attack(state);
        }
    }

    if (is_moving) {
        double dx = 0, dy = 0;
        if (next.x < target.x) dx = std::min(speed, target.x - next.x);
        if (next.x > target.x) dx = std::max(-speed, target.x - next.x);
        if (next.y < target.y) dy = std::min(speed, target.y - next.y);
        if (next.y > target.y) dy = std::max(-speed, target.y - next.y);

        Point potential_next(next.x + dx, next.y + dy);

        if (!Character::ch_interact(potential_next)) {
            next.x += dx;
            next.y += dy;
            shape->update_center_x(next.x);
            shape->update_center_y(next.y);
        } else {
            is_moving = false;
        }

        if (std::abs(next.x - target.x) < 1e-3 && std::abs(next.y - target.y) < 1e-3) {
            next.x = target.x;
            next.y = target.y;
            is_moving = false; 
        }
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
        next = Point(shape->center_x(), shape->center_y() + 43);
    } 
    else if (state == CharacterState::BACK) {
        next = Point(shape->center_x(), shape->center_y() - 43);
    }
    else if (state == CharacterState::LEFT) {
        next = Point(shape->center_x() - 43, shape->center_y());
    } else if (state == CharacterState::RIGHT) {
        next = Point(shape->center_x() + 43, shape->center_y());
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