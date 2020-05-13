#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iterator>
#include "player.h"
#include "token.h"
#include "background.h"
#include <unistd.h>

class Game{
    private:
    Player *player1; // always a person
    Player *player2; // computer or a person
    size_t board_size = 7;
    int *columns; //columns[x] returns y value of a first place in column were is it possible to put token || if column is full returns -1 
    size_t player_id_move = 1; //shows wich player should move
    size_t count_full_col = 0;
    Player *winner = nullptr;
    Background background;
    bool easyLevel;

    //display window parameters
    float window_width;
    float window_height;

    float column_seperate_size = 7.0;
    float start_col_x = 188.5;
    float start_col_y = 98.0;
    const float radius{22.5f};
    float tokenOutLineThhickness = 3.0;


    public:
    Game(float width,float height, Player *player_1, Player *player_2,  size_t board_size, bool easyLevel = true);
    size_t get_player_id_move( ){ return player_id_move; }

    Player* get_winner(){ return winner;}  
    Player* get_opponent(size_t player_id);

    int get_column(float x );
    void playerMove(Vector2i mouse_position);
    void display_board(RenderWindow &window );

    bool isItTheEndOfTheGame();
};

#endif //GAME_H