#include "game.h"


Game::Game(float width,float height, Player *player_1, Player *player_2,  size_t board_size, bool easyLevel){
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

Player* Game::get_opponent(size_t player_id){
    if(player_id == player1->get_player_id()) return player2;
    else return player1;
}

int Game::get_column(float x ){
    for(size_t i = 0; i < board_size; i++ ){
        float column_start_x = start_col_x + column_seperate_size*float(i+1)+radius*2*float(i);
        float column_end_x = column_start_x + 2*radius;
        if(x>=column_start_x && x<=column_end_x) return i;
    }
    return -1;

}

void Game::playerMove(Vector2i mouse_position){
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
    }
    else{ 
        if(player2->is_computer()){ //computer move
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
        }else{ // move of other person
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

void Game::display_board(RenderWindow &window ){
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

bool Game::isItTheEndOfTheGame(){
    if(count_full_col == board_size) return true;
    if(winner!=nullptr) return true;
    return false;
}