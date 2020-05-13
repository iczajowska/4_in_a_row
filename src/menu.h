#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "button.h"
#include "checkbox.h"
#include "textBox.h"

class Menu{
    private:
    Player *players[2];
    float window_width;
    float window_height;
    size_t board_size;
    Button startGameButton = Button( window_width/2.0f - 50.0f, 500.0f, 100.0f,50.0f,"img/button.png" ,"img/button_hover.png" );
    Checkbox checkbox = Checkbox(600.0f,100.0f,50.0f,50.0f,"img/unchecked.png", "img/check.png");
    Checkbox checkbox_level_easy = Checkbox(500.0f,330.0f,50.0f,50.0f,"img/unchecked.png", "img/check.png");
    TextBox textBox1;
    TextBox textBox2;
    Texture texture;
    Sprite sprite;

    public:
    Menu(float width, float height, size_t board_size) : window_width{width},window_height{height},board_size{board_size}{}

    bool isEasyLevel(){ return checkbox_level_easy.isBoxChecked(); }
    Player** display_menu(RenderWindow &window, std::string font_name);

    private:
    void setTexture(std::string imgPath);
    void checkIfHover(Vector2i mousePostion);
    bool checkClick(Vector2i mousePostion);

};


#endif //MENU_H