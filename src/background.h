#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Background{
    private:
    Texture texture;
    Sprite sprite;
    int x = 0;
    int y = 0;
    float width;
    float height;

    public:
    Background(){}
    Background(float w, float h):width{w},height{h}{}
    
    void display(RenderWindow &window){
        if(!this->texture.loadFromFile("img/background.png")){
            throw std::invalid_argument("Error: Cannot load background from file");
        }
        texture.setSmooth(true);
        this->sprite.setTexture(texture);
        window.draw(sprite);
    }
};
#endif // BACKGROUND_H