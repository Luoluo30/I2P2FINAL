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
    width = al_get_bitmap_width(bitmap);
    height = al_get_bitmap_height(bitmap);
    shape.reset(new Rectangle{p.x, p.y, p.x+width, p.y+height});
    hitbox = new Rectangle{p.x, p.y, p.x+width, p.y+height};
}

void Wall2::update() {

}

void Wall2::draw() {
    al_draw_bitmap(
        bitmap,
        shape->center_x() - width, 
        shape->center_y() - height, 
        0);                            
}

