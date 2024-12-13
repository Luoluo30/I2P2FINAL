#include "Enemy.h"
#include "EnemyGhost.h"
#include "../data/DataCenter.h"
#include "../data/ImageCenter.h"
#include "../Level.h"
#include "../Player.h"
#include "../Character.h"
#include "../shapes/Point.h"
#include "../shapes/Rectangle.h"
#include "../Wall.h"
#include "../Wall2.h"
#include "../Utils.h"
#include <allegro5/allegro_primitives.h>

using namespace std;

// fixed settings
enum class Dir {
	UP, DOWN, LEFT, RIGHT
};

Enemy *Enemy::create_enemy(EnemyType type, Point p) {
	switch(type) {
		case EnemyType::GHOST: {
			return new EnemyGhost{p};
		}
		case EnemyType::ENEMYTYPE_MAX: {}
	}
	GAME_ASSERT(false, "monster type error.");
}

// Dir convert_dir(const Point &v) {
// 	if(v.y < 0 && abs(v.y) >= abs(v.x))
// 		return Dir::UP;
// 	if(v.y > 0 && abs(v.y) >= abs(v.x))
// 		return Dir::DOWN;
// 	if(v.x < 0 && abs(v.x) >= abs(v.y))
// 		return Dir::LEFT;
// 	if(v.x > 0 && abs(v.x) >= abs(v.y))
// 		return Dir::RIGHT;
// 	return Dir::RIGHT;
// }

Enemy::Enemy(EnemyType type, Point p)
{
    //DataCenter *DC = DataCenter::get_instance();
	shape.reset(new Rectangle{p.x-21.5, p.y-21.5, p.x+21.5, p.y+21.5});
	this->type = type;
	dir = Dir::RIGHT;

}


void Enemy::update() {
    DataCenter *DC = DataCenter::get_instance();

    Point current_position = {shape->center_x(), shape->center_y()};
    Point next_position = current_position;

    if (DC->character->shape->overlap(Rectangle{
        next_position.x - 21.5,
        next_position.y - 21.5,
        next_position.x + 21.5,
        next_position.y + 21.5
    })) {
        DC->player->HP--; 
    }

    if (rand() % 100 < 1) { 
        change_direction();
    }

    if (dir == Dir::UP) {
        next_position.y -= speed;
    } else if (dir == Dir::DOWN) {
        next_position.y += speed;
    } else if (dir == Dir::LEFT) {
        next_position.x -= speed;
    } else if (dir == Dir::RIGHT) {
        next_position.x += speed;
    }

    Rectangle next_hitbox{
        next_position.x - 21.5,
        next_position.y - 21.5,
        next_position.x + 21.5,
        next_position.y + 21.5
    };

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
        return; 
    }
    shape->update_center_x(next_position.x);
    shape->update_center_y(next_position.y);
 
}


void
Enemy::draw() {
	ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *bitmap = IC->get("./assets/image/enemy/Ghost/UP_0.png");
	al_draw_bitmap(
		bitmap,
		shape->center_x() - al_get_bitmap_width(bitmap) / 2,
		shape->center_y() - al_get_bitmap_height(bitmap) / 2, 0);
}

void Enemy::change_direction()
{
    if (dir == Dir::UP) {
        dir = Dir::RIGHT;
    } else if (dir == Dir::RIGHT) {
        dir = Dir::DOWN;
    } else if (dir == Dir::DOWN) {
        dir = Dir::LEFT;
    } else if (dir == Dir::LEFT) {
        dir = Dir::UP;
    }
}

void Enemy::fix_position(Point &current_position) {
    DataCenter *DC = DataCenter::get_instance();

    while(true){
        Rectangle current_hitbox{
            current_position.x - 21.5,
            current_position.y - 21.5,
            current_position.x + 21.5,
            current_position.y + 21.5
        };

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

        if (dir == Dir::UP) {
            current_position.y += speed;
        } else if (dir == Dir::DOWN) {
            current_position.y -= speed; 
        } else if (dir == Dir::LEFT) {
            current_position.x += speed; 
        } else if (dir == Dir::RIGHT) {
            current_position.x -= speed; 
        }
    }
    shape->update_center_x(current_position.x);
    shape->update_center_y(current_position.y);
}



