#ifndef REM_H_INCLUDED
#define REM_H_INCLUDED
#include "Object.h"
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <string>
#include <vector>

enum class rDir;

class Rem : public Object
{
public:
    Rem(const Point &p);          
    void update();          
    void draw();    
    void change_direction();               
    void fix_position(Point &current_position); 
    Rectangle *hitbox;

private:
    
    double speed;                  
    std::vector<std::string> images; 
    int current_image_index;   
    double rotation_angle;             
    std::string current_image_path;
    rDir dir;
    bool is_alternate_image;
};

#endif
