#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"
#include "Checkbox.h"
#include "TextBox.h"

class Menu{
    private:
    Player *players[2];
    float window_width;
    float window_height;
    size_t board_size;
    Button startGameButton = Button( window_width/2.0f - 50.0f, 500.0f, 100.0f,50.0f,"img/button.png" ,"img/button_hover.png" );
    Checkbox checkbox = Checkbox(600.0f,100.0f,50.0f,50.0f,"img/unchecked.png", "img/check.png");
    TextBox textBox1;
    TextBox textBox2;
    Texture texture;
    Sprite sprite;

    public:
    Menu(float width, float height, size_t board_size) : window_width{width},window_height{height},board_size{board_size}{}

    void checkIfHover(Vector2i mousePostion){
        bool flag = startGameButton.isHovered(mousePostion);
        startGameButton.setHovered(flag);
    }

    bool checkClick(Vector2i mousePostion){ 
        if(checkbox.isHovered(mousePostion)) {
            checkbox.changeChecked();
            if(checkbox.isBoxChecked()) {
                this->setTexture("img/menu_1_pl.png");
            } else{
                this->setTexture("img/menu_2_pl.png");
            }
        } 
        if(textBox1.isHovered(mousePostion)&&!textBox1.isTextBoxSelected()){
            textBox1.setIsSelected(true);
        }
        if(!textBox1.isHovered(mousePostion)&&textBox1.isTextBoxSelected()){
            textBox1.setIsSelected(false);
        }
        if(!checkbox.isBoxChecked()){
            if(textBox2.isHovered(mousePostion)&&!textBox2.isTextBoxSelected()){
                textBox2.setIsSelected(true);
            }
            if(!textBox2.isHovered(mousePostion)&&textBox2.isTextBoxSelected()){
                textBox2.setIsSelected(false);
            }
        }
        if(startGameButton.isHovered(mousePostion)){
            if(textBox1.getText() == "") return false;
            if(!checkbox.isBoxChecked()){
                if(textBox2.getText() == "") return false;
                else return true;
            } else return true;
        }
        return false; 
    }

    Player** display_menu(RenderWindow &window){
        
        sf::Font MyFont;
        if (!MyFont.loadFromFile("font/Purisa, Regular.ttf"))
        {
            throw std::invalid_argument("Error: Cannot load font file");
        }
        

        sf::Text text;
        const Color fontColor = Color::Black;
        text.setFont(MyFont);
        text.setCharacterSize(50);
        text.setFillColor(fontColor);
        this->setTexture("img/menu_2_pl.png");

        textBox1 = TextBox( 380, 230, 300, 50, 12, MyFont, false);
        textBox2 = TextBox( 380, 330, 300, 50, 12, MyFont, false);

        

        bool startGame = false;

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                    Vector2i localPosition = Mouse::getPosition(window);
                    std::cout<<localPosition.x<<" "<<localPosition.y<<"\n";
                    startGame = this->checkClick(localPosition);
                    break;
                }

                if(event.type == Event::TextEntered){
                    textBox1.typeCharacter(event);
                    textBox2.typeCharacter(event);
                    break;
                }
            }
            Vector2i localPosition = Mouse::getPosition(window);
            window.clear();
            window.draw(sprite);
            this->checkIfHover(localPosition);
            startGameButton.display(window);
            checkbox.display(window);
            textBox1.display(window);

            if(!checkbox.isBoxChecked())
            textBox2.display(window);
            
            window.display();
            if(startGame) break;
        }

        std::string name = textBox1.getText();
        players[0] = new Player(1,name,false,board_size); 

        if(checkbox.isBoxChecked()) players[1] = new Player(2,true,board_size);
        else{
            name = textBox2.getText();
            players[1] = new Player(2,name,false,board_size); 
        }

        return players;
    }

    private:
    void setTexture(std::string imgPath){
        if(!texture.loadFromFile(imgPath)){
            throw std::invalid_argument("Error: Cannot load image plain from file");
        }

        texture.setSmooth(true);
        sprite.setTexture(texture);
    }
};


#endif //MENU_H