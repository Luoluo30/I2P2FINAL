#include "Fruit.h"
#include "data/DataCenter.h"
#include "data/ImageCenter.h"
#include "shapes/Point.h"
#include <allegro5/bitmap_draw.h>
#include "shapes/Rectangle.h"

void Fruit::init() {
    constexpr char  fruit_img_path[] = "./assets/image/Fruit.png";
    DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();
    
  
    
    
}
void Fruit::draw() {
    constexpr char  fruit_img_path[] = "./assets/image/Fruit.png";
    ImageCenter *IC = ImageCenter::get_instance();
   
    
    bitmap = IC->get(fruit_img_path);

	al_draw_bitmap(
		bitmap,
		shape->center_x() - al_get_bitmap_width(bitmap)/2,
		shape->center_y() - al_get_bitmap_height(bitmap)/2, 0);
}
