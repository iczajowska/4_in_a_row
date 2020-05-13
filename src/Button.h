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

    bool isHovered(Vector2i mouse_position){
        float m_x = float(mouse_position.x);
        float m_y = float(mouse_position.y);

        return (m_x>=x && m_x<=x+width && m_y>=y && m_y<=y+height);
    }

    void setHovered(bool flag){ this->hovered = flag;}

    void display(RenderWindow &window){
        if(hovered){
            if(!this->texture.loadFromFile(imgPathHovered)){
                throw std::invalid_argument("Error: Cannot load button img from file");
            }
        }
        else{
            if(!this->texture.loadFromFile(imgPath)){
                throw std::invalid_argument("Error: Cannot load button img from file");
            }
        }
        this->texture.setSmooth(true);
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(this->x,this->y);
        window.draw(sprite);
    }
};


#endif //BUTTON_H