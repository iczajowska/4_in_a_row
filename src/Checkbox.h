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

    bool isHovered(Vector2i mouse_position){
        float m_x = float(mouse_position.x);
        float m_y = float(mouse_position.y);

        return (m_x>=x && m_x<=x+width && m_y>=y && m_y<=y+height);
    }

    void changeChecked(){
        if(isChecked) isChecked = false;
        else isChecked = true;
    }

    bool isBoxChecked(){
        return isChecked;
    }

    void display(RenderWindow &window){
        if(isChecked){
            if(!this->texture.loadFromFile(imgPathChecked)){
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


#endif //CHECKBOX_H