#ifndef TEXTBOX_H
#define TEXTBOX_H
#define BLINK_PERIOD 1.f
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace sf;

#define ENTER_KEY 13
#define DELETE_KEY 8

class TextBox{
    private:
    Text text;
    std::ostringstream input;
    float padding = 5.0;
    float x;
    float y;
    float width;
    float height;
    bool isSelected;
    size_t maxLength;

    public:
    TextBox(){};
    TextBox( float x, float y, float width, float height, size_t maxLength, sf::Font &MyFont, bool selected);

    bool isTextBoxSelected(){ return isSelected; }
    std::string getText(){ return input.str(); }
    void display(RenderWindow &window){ window.draw(text); }

    void inputLogic(int charTyped);
    void typeCharacter(Event in);
    bool isHovered(Vector2i mouse_position);
    void setIsSelected(bool flag);
    void deleteLastCharacter();    
};


#endif //TEXTBOX_H