#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <set> 
#include <time.h>
#include "token.h"

class Player{
    private:
    size_t player_id;
    size_t game_size;
    std::string name;
    bool isComputer;
    std::set <Token> tokensSet;

    public:
    Player(size_t player_id,bool isComputer=true, size_t size = 8): player_id{player_id}, game_size{size}, name{""}, isComputer(isComputer){}
    Player( size_t player_id,std::string name,bool isComputer=true,size_t size = 8): player_id{player_id}, game_size{size},name{name}, isComputer(isComputer) {}

    bool is_computer() const { return this->isComputer; }

    size_t get_game_size() const{ return this->game_size; }
    size_t get_player_id() const { return this->player_id; }
    std::string get_name() const{ return this->name;}

    void set_name(std::string n){ name = n; }
    std::set <Token> get_tokens_set() const { return this->tokensSet; }

    void add_token( size_t x, size_t y);
    void add_token(Token token);
    void remove_token(size_t x, size_t y);
    bool is_token_at_position(size_t x, size_t y);
    bool is_token_in_set(Token token);

    size_t choose_rand_column(int *columns, Player* opponent); //medium level
    size_t choose_rand_column(int *columns); // amateur level

    bool check_if_win(size_t x, size_t y); // (x,y) is the position of last inserted token 

    bool check_if_win_test(size_t x, size_t y); 
    // (x,y) check after putting this token if player wins. Token (x,y) might not be inserted to the set of tokens
};
#endif //PLAYER_H