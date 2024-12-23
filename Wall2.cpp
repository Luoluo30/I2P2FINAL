#include "Wall2.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <allegro5/bitmap_draw.h>
#include "Utils.h"

Wall2::Wall2(const Point &p, const std::string &path) {
    ImageCenter *IC = ImageCenter::get_instance();
    bitmap = IC->get(path);
    width = 43;
    height = 43;
    shape.reset(new Rectangle{p.x - width / 2, p.y - height / 2, p.x + width / 2, p.y + height / 2});
    hitbox = new Rectangle{p.x - width / 2, p.y - height / 2, p.x + width / 2, p.y + height / 2};
}

void Wall2::update() {

}

void Wall2::draw() {
    al_draw_bitmap(
        bitmap,
        shape->center_x() - width / 2, 
        shape->center_y() - height / 2, 
        0);                            
}

