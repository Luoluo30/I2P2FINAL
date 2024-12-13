#include "Wall.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <allegro5/bitmap_draw.h>
#include "Utils.h"

Wall::Wall(const Point &p, const std::string &path) {
    ImageCenter *IC = ImageCenter::get_instance();
    bitmap = IC->get(path);
    width = 43;
    height = 43;
    shape.reset(new Rectangle{p.x - width / 2, p.y - height / 2, p.x + width / 2, p.y + height / 2});
    hitbox = new Rectangle{p.x - width / 2, p.y - height / 2, p.x + width / 2, p.y + height / 2};
}

void Wall::update() {

}

void Wall::draw() {
    al_draw_bitmap(
        bitmap,
        shape->center_x() - width / 2, 
        shape->center_y() - height / 2, 
        0);                            
}

void Wall::destroy(){
    if (hitbox) {
        delete hitbox;
        hitbox = nullptr;
    } else {
        debug_log("Warning: hitbox already deleted.\n");
    }

    if (bitmap) {
        al_destroy_bitmap(bitmap);
        bitmap = nullptr;
    } else {
        debug_log("Warning: bitmap already destroyed.\n");
    }

    debug_log("Wall destroyed.\n");
}
