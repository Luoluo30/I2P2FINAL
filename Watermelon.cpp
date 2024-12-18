#include "Watermelon.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include <stdio.h>
#include "data/ImageCenter.h"



Watermelon::Watermelon(const Point &p) {
    //DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
    bitmap = IC->get("./assets/image/Fruit/watermelon.png");

    width = al_get_bitmap_width(bitmap);
    height = al_get_bitmap_height(bitmap);
    hitbox = new Rectangle{p.x - width / 2, p.y - height / 2, p.x + width / 2, p.y + height / 2};

    
    shape.reset(new Rectangle{
    p.x - width / 2,
    p.y - height / 2,
    p.x + width / 2,
    p.y + height / 2
});

}

void Watermelon::update(){

}


void Watermelon::draw() {
    al_draw_bitmap(
        bitmap,
        shape->center_x() - width / 2,
        shape->center_y() - height / 2,
        0 
    );
}

void Watermelon::destroy(){
    if (bitmap) {
        al_destroy_bitmap(bitmap);
        bitmap = nullptr;
    } 

}
