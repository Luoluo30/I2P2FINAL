#include "Fruit.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "shapes/Point.h"
#include <allegro5/bitmap_draw.h>

void Fruit::init() {

    
    ImageCenter *IC = ImageCenter::get_instance();
    bitmap = IC->get("./assets/image/Fruit.png");
    constexpr char  fruit_img_path[] = "./assets/image/Fruit.png";
    bitmap = IC->get(fruit_img_path);

    
  
   
}

void
Fruit::draw() {
	al_draw_bitmap(
		bitmap,
		shape->center_x() - al_get_bitmap_width(bitmap)/2,
		shape->center_y() - al_get_bitmap_height(bitmap)/2, 0);
}
