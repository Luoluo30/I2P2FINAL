#include "Wall.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <allegro5/bitmap_draw.h>

Wall::Wall(const Point &p, const std::string &path) {
    ImageCenter *IC = ImageCenter::get_instance();
    bitmap = IC->get(path);
    width = al_get_bitmap_width(bitmap);
    height = al_get_bitmap_height(bitmap);
    shape.reset(new Rectangle{p.x, p.y, p.x+width, p.y+height});
}

void Wall::update() {

}

void Wall::draw() {
    al_draw_scaled_bitmap(
        bitmap,
        0, 0,              
        width,        
        height,      
        shape->center_x() - width / 20,  
        shape->center_y() - height / 20, 
        width / 10,  
        height / 10,   
        0);                             
}