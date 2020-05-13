#include "player.h"

void Player::add_token( size_t x, size_t y){
    if(x>=game_size||y>=game_size||x<0||y<0 )
    throw std::out_of_range("Error: wrong token coordinates; addToken function");

    Point tmpPoint = Point(x,y);
    Token tmpToken = Token(player_id,tmpPoint);
    if(tokensSet.count(tmpToken) == 0){
        tokensSet.insert(tmpToken);
    } else throw std::invalid_argument("Error: Argument is already in the set");
}

void Player::add_token(Token token){
    size_t x = token.get_point().get_x();
    size_t y = token.get_point().get_y();
    if(x>=game_size||y>=game_size||x<0||y<0 )
    throw std::out_of_range("Error: wrong token coordinates; addToken function");

    if(tokensSet.count(token) == 0){
        tokensSet.insert(token);
    } else throw std::invalid_argument("Error: Argument is already in the set");
}

void Player::remove_token(size_t x, size_t y){
    if(x>=game_size||y>=game_size||x<0||y<0 )
    throw std::out_of_range("Error: wrong token coordinates; addToken function");

    Point tmpPoint = Point(x,y);
    Token tmpToken = Token(player_id,tmpPoint);
    std::set<Token>::iterator it;
    it = tokensSet.find(tmpToken);
    if( it != tokensSet.end()){
        tokensSet.erase(tmpToken);
    } else throw std::invalid_argument("Error: Argument is already in the set");

}

bool Player::is_token_at_position(size_t x, size_t y){
    Point tmpPoint = Point(x,y);
    Token tmp = Token(player_id,tmpPoint);
    if(tokensSet.find(tmp)!=tokensSet.end()){
        return true;
    }
    return false;

}

bool Player::is_token_in_set(Token token){ 
    if(tokensSet.find(token)!=tokensSet.end()){
        return true;
    }
    return false;
}

size_t Player::choose_rand_column(int *columns, Player* opponent){ //medium level
    srand(time(NULL));
    if(!isComputer){
        throw std::logic_error("Error: Player is not a computer");
    } else{
        for(size_t i = 0 ; i<this->game_size; i++ ){
            if(columns[i]>0 && this->check_if_win_test(i,columns[i])){
                return i;
            }
        }
        for(size_t i=0; i<this->game_size; i++){
            if(columns[i]>0 && opponent->check_if_win_test(i,columns[i])){
                return i;
            }
        }

        size_t col = rand()%game_size;
        while(columns[col]<0){
            col = rand()%game_size;
        }
        return col;
    }   
}

size_t Player::choose_rand_column(int *columns){ // amateur level
    srand(time(NULL));
    if(!isComputer){
        throw std::logic_error("Error: Player is not a computer");
    } else{
        for(size_t i = 0 ; i<this->game_size; i++ ){
            if(columns[i]>0 && this->check_if_win_test(i,columns[i])){
                return i;
            }
        }
        size_t col = rand()%game_size;
        while(columns[col]<0){
            col = rand()%game_size;
        }
        return col;
    }   
}


bool Player::check_if_win(size_t x, size_t y){ // (x,y) is the position of last inserted token 
    if(!(x>=0 && x<game_size) || !(y>=0 && y<game_size)) throw std::invalid_argument("Error: wrong coordinates (x,y)");

    int sum_diag_top_down = 1;              // ⤡
    int sum_diag_down_top = 1;              // ⤢
    int sum_horizontal = 1;                 // ⟷
    int sum_vertical = 1;                   // ↕
    
    bool left_up_diag = true;               // ↖
    bool left_down_diag = true;             // ↙
    bool left = true;                       // ←
    bool up = true;                         // ↑
    bool right_up_diag = true;              // ↗
    bool right = true;                      // →
    bool right_down_diag = true;            // ↘
    bool down = true;                       // ↓

    for(int i=0; i<4; i++){
        if(i==0){
            if(!this->is_token_at_position(x,y)) return false;
        } else{
            if(right_up_diag && x+i<game_size && y-i>=0){
                if(this->is_token_at_position(x+i, y-i)) sum_diag_down_top++;
                else right_up_diag = false;
            }
            if(left_down_diag && x-i>=0 && x-i>=0 && y+i <game_size ){
                if(this->is_token_at_position(x-i, y+i)) sum_diag_down_top++;
                else left_down_diag = false;
            }
            if(left_up_diag && x-i>=0 && y-i >=0){
                if(this->is_token_at_position(x-i,y-i)) sum_diag_top_down++;
                else left_up_diag = false;                    
            }
            if(right_down_diag && x+i<game_size && y+i<game_size){
                if(this->is_token_at_position(x+i,y+i)) sum_diag_top_down++;
                else right_down_diag = false;
            }
            if(right && x+i < game_size){
                if(this->is_token_at_position(x+i, y)) sum_horizontal++;
                else right = false;
            }
            if(left && x-i >= 0 ){
                if(this->is_token_at_position(x-i, y)) sum_horizontal++;
                else left = false;
            }
            if( up && y-i >=0 ){
                if(this->is_token_at_position(x,y-i)) sum_vertical++;
                else up = false;
            }
            if( down && y+i < game_size){
                if(this->is_token_at_position(x, y+i)) sum_vertical++;
                else down = false;
            }
        }

    }
    if(sum_diag_top_down>=4 || sum_diag_down_top>=4 || sum_horizontal>=4 || sum_vertical>=4) return true;
    else return false;
}

bool Player::check_if_win_test(size_t x, size_t y){ // (x,y) check after putting this token if player wins. Token (x,y) might not be inserted to the set of tokens
    if(!(x>=0 && x<game_size) || !(y>=0 && y<game_size)) throw std::invalid_argument("Error: wrong coordinates (x,y)");

    int sum_diag_top_down = 1;              // ⤡
    int sum_diag_down_top = 1;              // ⤢
    int sum_horizontal = 1;                 // ⟷
    int sum_vertical = 1;                   // ↕
    
    bool left_up_diag = true;               // ↖
    bool left_down_diag = true;             // ↙
    bool left = true;                       // ←
    bool up = true;                         // ↑
    bool right_up_diag = true;              // ↗
    bool right = true;                      // →
    bool right_down_diag = true;            // ↘
    bool down = true;                       // ↓

    for(int i=1; i<4; i++){
        if(right_up_diag && x+i<game_size && y-i>=0){
            if(this->is_token_at_position(x+i, y-i)) sum_diag_down_top++;
            else right_up_diag = false;
        }
        if(left_down_diag && x-i>=0 && x-i>=0 && y+i <game_size ){
            if(this->is_token_at_position(x-i, y+i)) sum_diag_down_top++;
            else left_down_diag = false;
        }
        if(left_up_diag && x-i>=0 && y-i >=0){
            if(this->is_token_at_position(x-i,y-i)) sum_diag_top_down++;
            else left_up_diag = false;                    
        }
        if(right_down_diag && x+i<game_size && y+i<game_size){
            if(this->is_token_at_position(x+i,y+i)) sum_diag_top_down++;
            else right_down_diag = false;
        }
        if(right && x+i < game_size){
            if(this->is_token_at_position(x+i, y)) sum_horizontal++;
            else right = false;
        }
        if(left && x-i >= 0 ){
            if(this->is_token_at_position(x-i, y)) sum_horizontal++;
            else left = false;
        }
        if( up && y-i >=0 ){
            if(this->is_token_at_position(x,y-i)) sum_vertical++;
            else up = false;
        }
        if( down && y+i < game_size){
            if(this->is_token_at_position(x, y+i)) sum_vertical++;
            else down = false;
        }
    }
    if(sum_diag_top_down>=4 || sum_diag_down_top>=4 || sum_horizontal>=4 || sum_vertical>=4) return true;
    else return false;
}
    
