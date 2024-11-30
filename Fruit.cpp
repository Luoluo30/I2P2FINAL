#include "Fruit.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include "shapes/Rectangle.h"
#include <stdio.h>
#include "data/ImageCenter.h"


namespace FruitSetting
{
    static constexpr char png_root_path[50] = "./assets/image/Fruit/fruit.png";
    
}

void Fruit::init() {
    // 获取 DataCenter 实例，获取窗口宽度和高度
    DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();

    // 静态定义水果图像路径
    static constexpr char png_path[] = "./assets/image/Fruit/fruit.png";

    // 从 ImageCenter 加载水果图片
    ALLEGRO_BITMAP *fruit_bitmap = IC->get(png_path);
    if (!fruit_bitmap) {
        throw std::runtime_error("Failed to load fruit image: " + std::string{png_path});
    }

    // 获取图像宽度和高度
    width = al_get_bitmap_width(fruit_bitmap);
    height = al_get_bitmap_height(fruit_bitmap);

    // 初始化形状数据为居中
    shape.reset(new Rectangle{
        DC->window_width / 2 - width / 2,
        DC->window_height / 2 - height / 2,
        DC->window_width / 2 + width / 2,
        DC->window_height / 2 + height / 2
    });
}




void Fruit::draw() {
    // 获取 DataCenter 实例和当前形状中心点
    DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IC = ImageCenter::get_instance();

    // 静态定义水果图像路径
    static constexpr char png_path[] = "./assets/image/Fruit/fruit.png";

    // 获取水果图像
    ALLEGRO_BITMAP *fruit_bitmap = IC->get(png_path);
    if (!fruit_bitmap) {
        throw std::runtime_error("Failed to load fruit image: " + std::string{png_path});
    }

    // 绘制水果图像居中于当前形状
    al_draw_bitmap(
        fruit_bitmap,
        shape->center_x() - width / 2,
        shape->center_y() - height / 2,
        0 // 无额外绘制标志
    );
}


