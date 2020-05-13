#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unistd.h>
#include "Game.h"
#include "Menu.h"

using namespace sf;

const int WIDTH = 800;
const int HEIGHT = 600;

const size_t board_size = 8;

void visualization(){
    RenderWindow window{VideoMode(WIDTH, HEIGHT), "4 in a Row"};
    window.setFramerateLimit(60);

    Menu menu(WIDTH,HEIGHT,board_size);
    Player **players = menu.display_menu(window);

    Game game(WIDTH,HEIGHT,players[0],players[1], board_size, false);

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
                game.playerMove(localPosition);

            }
        }

        window.clear();
        game.diaplay_board(window);
        window.display();
        if(game.isItTheEndOfTheGame()) break;
    }
    sleep(1);

    sf::Font MyFont;
    if (!MyFont.loadFromFile("font/Purisa, Regular.ttf"))
    {
        throw std::invalid_argument("Error: Cannot load font file");
    }

    Texture texture;
    Sprite sprite;
    sf::Text text;
    const Color fontColor = Color::Black;
    text.setFont(MyFont);
    text.setCharacterSize(50);
    text.setFillColor(fontColor);

    Player *winner = game.get_winner();
    if(winner==nullptr){ //draw
        if(!texture.loadFromFile("img/draw.png")){
            throw std::invalid_argument("Error: Cannot load image draw from file");
        }   
    } else{
        if(winner->is_computer()){
            if(!texture.loadFromFile("img/lose.png")){
                throw std::invalid_argument("Error: Cannot load image lose from file");
            }
            
        }else{
            Player* opponent = game.get_opponent(winner->get_player_id());
            if(opponent->is_computer()){
                if(!texture.loadFromFile("img/win.png")){
                    throw std::invalid_argument("Error: Cannot load image lose from file");
                }
            }else {         
                if(!texture.loadFromFile("img/plain.png")){
                    throw std::invalid_argument("Error: Cannot load image plain from file");
                }
                std::string str ="Player "+ winner->get_name()+" wins!!!";
                text.setString(str);
            }
        }
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(WIDTH/2.0f,HEIGHT/2.0f));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        
        window.draw(sprite);
        window.draw(text);
        window.display();
    }

    
}

#endif 
