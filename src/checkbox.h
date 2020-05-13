#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Checkbox{
    private:
    float x;
    float y;
    float width;
    float height;
    bool isChecked = false;
    std::string imgPath;
    std::string imgPathChecked;
    Texture texture;
    Sprite sprite;

    public:
    Checkbox(float x, float y, float width, float height, std::string imgPath, std::string imgPathChecked): x{x},y{y},width{width},height{height}, imgPath{imgPath},imgPathChecked{imgPathChecked}{}

    bool isBoxChecked(){ return isChecked; }
    bool isHovered(Vector2i mouse_position);
    void changeChecked();
    void display(RenderWindow &window);
};


#endif //CHECKBOX_H