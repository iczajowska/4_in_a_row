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
    Game(float width,float height, Player *player_1, Player *player_2,  size_t board_size, bool easyLevel = true){
        this->easyLevel = easyLevel;
        window_width = width;
        window_height = height;

        this->player1 = player_1;
        this->player2 = player_2;
        this->board_size = board_size;
        columns = new int[board_size];
        for (int i=0; i<int(board_size); i++){
            columns[i] = int(board_size) - 1;
        }
        this->background = Background(width,height);
    }
    size_t get_player_id_move( ){ return player_id_move; }

    int get_column(float x ){
        for(size_t i = 0; i < board_size; i++ ){
            float column_start_x = start_col_x + column_seperate_size*float(i+1)+radius*2*float(i);
            float column_end_x = column_start_x + 2*radius;
            if(x>=column_start_x && x<=column_end_x) return i;
        }
        return -1;

    }

    void playerMove(Vector2i mouse_position){
        int x = mouse_position.x;
        int y = mouse_position.y;

        size_t token_y;
        size_t token_x;

        if(player1->get_player_id() == player_id_move){ //first player is allways a person; second might be computer or other player
            float board_end_x = (column_seperate_size +2*radius)*float(board_size) + column_seperate_size +start_col_x;
            float board_end_y = board_end_x - start_col_x + start_col_y;
            if(float(x)< start_col_x || float(y)< start_col_y || float(x)> board_end_x || float(y)>board_end_y) return;
            int col = this->get_column(float(x));
            if(col == -1 || columns[col]<0) return;
            token_y = columns[col];
            token_x = col;
            columns[col] --;
            if(columns[col]<0) count_full_col++;
            player1->add_token(token_x,token_y);
            if(player1->check_if_win(token_x,token_y)){
                this->winner = player1;
                return;
            }

            player_id_move = 1-player_id_move;
/*
            if(!player2->is_computer()) player_id_move = 1-player_id_move;
            else{
                if( count_full_col == board_size) {
                    return; //every column is full
                }
                
                if(!easyLevel) token_x = player2->choose_rand_column(columns, player1);
                else token_x = player2->choose_rand_column(columns);
                
                token_y = columns[token_x];
                columns[token_x]--;
                
                if(columns[token_x]<0) count_full_col++;
                player2->add_token(token_x,token_y);

                if(player2->check_if_win(token_x,token_y)){
                    this->winner = player2;
                    return;
                }  
            }
 */       }
        else{ // move of other person
            if(player2->is_computer()){
                player_id_move = 1-player_id_move;
                if( count_full_col == board_size) {
                    return; //every column is full
                }
                
                if(!easyLevel) token_x = player2->choose_rand_column(columns, player1);
                else token_x = player2->choose_rand_column(columns);
                
                token_y = columns[token_x];
                columns[token_x]--;
                
                if(columns[token_x]<0) count_full_col++;
                player2->add_token(token_x,token_y);

                if(player2->check_if_win(token_x,token_y)){
                    this->winner = player2;
                    return;
                }
            }else{
                float board_end_x = (column_seperate_size +2*radius)*float(board_size) + column_seperate_size +start_col_x;
                float board_end_y = board_end_x - start_col_x + start_col_y;
                if(float(x)< start_col_x || float(y)< start_col_y || float(x)> board_end_x || float(y)>board_end_y) return;
                int col = this->get_column(float(x));
                if(col == -1 || columns[col]<0) return;

                token_y = columns[col];
                token_x = col;
                columns[col] --;
                if(columns[col]<0) count_full_col++;

                player2->add_token(token_x,token_y);
                player_id_move = 1-player_id_move;
                if(player2->check_if_win(token_x,token_y)){
                    this->winner = player2;
                    return;
                }  
            }

        }
    }

    void diaplay_board(RenderWindow &window ){
        background.display(window);

        std::set <Token> tokens = player1->get_tokens_set();
        std::set<Token>::iterator it = tokens.begin();
        while(it!= tokens.end()){
            Token t = *it;
            t.display(window, start_col_x,start_col_y, board_size, column_seperate_size , radius, tokenOutLineThhickness);
            it++;
        }

        tokens = player2->get_tokens_set();

        it = tokens.begin();
        while(it!= tokens.end()){
            Token t = *it;
            t.display(window, start_col_x,start_col_y, board_size, column_seperate_size , radius, tokenOutLineThhickness);
            it++;
        }

    }

    bool isItTheEndOfTheGame(){
        if(count_full_col == board_size) return true;
        if(winner!=nullptr) return true;
        return false;
    }

    Player* get_winner(){
        return winner;
    }

    Player* get_opponent(size_t player_id){
        if(player_id == player1->get_player_id()) return player2;
        else return player1;
    }
};

#endif //GAME_H