#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Button{
    private:
    float x;
    float y;
    float width;
    float height;
    bool hovered = false;
    std::string imgPath;
    std::string imgPathHovered;
    Texture texture;
    Sprite sprite;

    public:
    Button(float x, float y, float width, float height, std::string imgPath, std::string imgPathHovered): x{x},y{y},width{width},height{height}, imgPath{imgPath},imgPathHovered{imgPathHovered}{}

    void setHovered(bool flag){ this->hovered = flag;}
    bool isHovered(Vector2i mouse_position);
    void display(RenderWindow &window);
};


#endif //BUTTON_H