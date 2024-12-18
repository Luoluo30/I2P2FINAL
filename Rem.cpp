#include "Rem.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "Wall.h"
#include "Wall2.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>
#include <cmath>
#include "player.h"
#include "character.h"

// fixed settings
enum class rDir {
	UP, DOWN, LEFT, RIGHT
};

Rem::Rem(const Point &p)
{
    speed = 2;
    current_image_index = 0;
	images.push_back("./assets/image/enemy/Rem/UP_1.png");
    images.push_back("./assets/image/enemy/Rem/UP_0.png");
    shape.reset(new Rectangle{p.x - 21.5, p.y - 21.5, p.x + 21.5, p.y + 21.5});
    hitbox = new Rectangle(p.x - 21.5, p.y - 21.5, p.x + 21.5, p.y + 21.5);
    current_image_path = images[current_image_index];
    dir = rDir::RIGHT;
}

void Rem::update() {
    static double last_update_time = 0;
    DataCenter* DC = DataCenter::get_instance();
    Point current_position = {hitbox->center_x(), hitbox->center_y()};
    Point next_position = current_position;

    if (DC->character->invincible == false){
        if (DC->character->shape->overlap(Rectangle{
            next_position.x - 21.5,
            next_position.y - 21.5,
            next_position.x + 21.5,
            next_position.y + 21.5
        })) {
            DC->player->HP--; 
        }
    }

    if (rand() % 100 < 1) {
        change_direction();
    }

    if (dir == rDir::UP) {
        next_position.y -= speed;
    } else if (dir == rDir::DOWN) {
        next_position.y += speed;
    } else if (dir == rDir::LEFT) {
        next_position.x -= speed;
    } else if (dir == rDir::RIGHT) {
        next_position.x += speed;
    }

    Rectangle next_hitbox = Rectangle(
        next_position.x - 21.5, next_position.y - 21.5,
        next_position.x + 21.5, next_position.y + 21.5
    );

    bool will_collide = false;
    for (const auto &wall : DC->walls) {
        if (wall->hitbox->overlap(next_hitbox)) {
            will_collide = true;
            break;
        }
    }
    for (const auto &wall2 : DC->walls2) {
        if (wall2->hitbox->overlap(next_hitbox)) {
            will_collide = true;
            break;
        }
    }

    if (will_collide) {
        fix_position(current_position);
        change_direction();
    } else {
        hitbox->update_center_x(next_position.x);
        hitbox->update_center_y(next_position.y);
    }

    double current_time = al_get_time();
    if (current_time - last_update_time >= 10.0) {
        is_alternate_image = true;
        last_update_time = current_time;
    }

    if (is_alternate_image && current_time - last_update_time >= 0.1) {
        is_alternate_image = false; 
    }
}

void Rem::draw() {
    ImageCenter* IC = ImageCenter::get_instance();
    ALLEGRO_BITMAP* bitmap = IC->get(current_image_path);

    if (is_alternate_image) {
        bitmap = IC->get(images[1]);
    } else {
        bitmap = IC->get(images[0]);
    }

    al_draw_rotated_bitmap(
        bitmap,
        al_get_bitmap_width(bitmap) / 2,
        al_get_bitmap_height(bitmap) / 2,
        hitbox->center_x(),
        hitbox->center_y(),
        rotation_angle,
        0
    );
}

void Rem::change_direction() {
    if (dir == rDir::UP) {
        dir = rDir::RIGHT;
    } else if (dir == rDir::RIGHT) {
        dir = rDir::DOWN;
    } else if (dir == rDir::DOWN) {
        dir = rDir::LEFT;
    } else if (dir == rDir::LEFT) {
        dir = rDir::UP;
    }
}

void Rem::fix_position(Point &current_position) {
    DataCenter *DC = DataCenter::get_instance();

    while (true) {
        Rectangle current_hitbox = Rectangle(
            current_position.x - 21.5,
            current_position.y - 21.5,
            current_position.x + 21.5,
            current_position.y + 21.5
        );

        bool still_colliding = false;

        for (const auto &wall : DC->walls) {
            if (wall->hitbox->overlap(current_hitbox)) {
                still_colliding = true;
                break;
            }
        }
        for (const auto &wall2 : DC->walls2) {
            if (wall2->hitbox->overlap(current_hitbox)) {
                still_colliding = true;
                break;
            }
        }

        if (!still_colliding) {
            break;
        }

        if (dir == rDir::UP) {
            current_position.y += speed;
        } else if (dir == rDir::DOWN) {
            current_position.y -= speed; 
        } else if (dir == rDir::LEFT) {
            current_position.x += speed; 
        } else if (dir == rDir::RIGHT) {
            current_position.x -= speed; 
        }
    }

    hitbox->update_center_x(current_position.x);
    hitbox->update_center_y(current_position.y);
}