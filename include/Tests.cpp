#include <iostream>
#include <gtest/gtest.h>
#include "src/player.h"
#include "src/token.h"
#include "src/point.h"
#include "src/Game.h"


using namespace std;
using namespace ::testing;

TEST(TokenTest, OperatorTest) {
    const Token t_0_0 = Token(1,0,0);
    const Token t_1_1 = Token(1,1,1);
    const Token t_0_1 = Token(1,0,1);
    const Token t_1_0 = Token(1,1,0);
    
    EXPECT_TRUE(t_0_0.operator<(t_1_1));
    EXPECT_FALSE(t_0_1.operator<(t_0_0));
    EXPECT_TRUE(t_0_1.operator<(t_1_0));
}

TEST(PlayerTest, construction){
    const Player player_1 = Player(1);
    ASSERT_EQ(player_1.get_game_size(), 8 );
    ASSERT_TRUE(player_1.is_computer());
    ASSERT_EQ(player_1.get_name(),"");

    const Player player_2 = Player(2,"Henryk",false,10);
    ASSERT_EQ(player_2.get_game_size(), 10 );
    ASSERT_FALSE(player_2.is_computer());
    ASSERT_EQ(player_2.get_name(), "Henryk");
}

TEST(PlayerTest, Add_Remove_Tokens){
    const Token t_0_0 = Token(1,0,0);
    const Token t_1_1 = Token(1,1,1);
    const Token t_0_1 = Token(1,0,1);
    const Token t_1_0 = Token(1,1,0);

    Player p_1 = Player(1);

    p_1.add_token(t_0_0);
    EXPECT_TRUE(p_1.is_token_at_position(0,0));
    EXPECT_TRUE(p_1.is_token_in_set(t_0_0));
    EXPECT_THROW(p_1.add_token(t_0_0), invalid_argument);
    EXPECT_THROW(p_1.add_token(0,-10), out_of_range);
    EXPECT_FALSE(p_1.is_token_in_set(t_1_1));
    EXPECT_FALSE(p_1.is_token_in_set(t_1_0));
    EXPECT_FALSE(p_1.is_token_in_set(t_0_1));
    EXPECT_FALSE(p_1.is_token_at_position(1,1));
    p_1.add_token(t_1_1);
    EXPECT_TRUE(p_1.is_token_in_set(t_1_1));
    EXPECT_TRUE(p_1.is_token_at_position(1,1));
    p_1.remove_token(1,1);
    EXPECT_FALSE(p_1.is_token_in_set(t_1_1));
    EXPECT_FALSE(p_1.is_token_at_position(1,1));
}

TEST(PlayerTest,ChooseRandomColumn){
    Player p_1(1);
    Player p_2(2,false);
    int columns[8] = {7,7,7,7,7,7,7,7};
    size_t num = p_1.choose_rand_column(columns);
    for(int i=0; i<30; i++){
        EXPECT_TRUE(num>=0 && num<8);
        num = p_1.choose_rand_column(columns);
    }
    EXPECT_THROW(p_2.choose_rand_column(columns), logic_error);
}

TEST(PlayerTest, TestPlayerWin){
    {
        Player p_1(2, false);
        EXPECT_THROW(p_1.check_if_win(-1,0), invalid_argument);
        EXPECT_THROW(p_1.check_if_win(0,-1), invalid_argument);
        EXPECT_THROW(p_1.check_if_win(8,0), invalid_argument);
        EXPECT_THROW(p_1.check_if_win(0,8), invalid_argument);
    }

    {
        // check diagonal top - down ⤡
        Player p_1(2, false);
        p_1.add_token(0,0);
        p_1.add_token(1,1);
        p_1.add_token(2,2);
        p_1.add_token(3,3);
        EXPECT_TRUE(p_1.check_if_win(0,0));
        EXPECT_TRUE(p_1.check_if_win(2,2));
        EXPECT_TRUE(p_1.check_if_win(3,3));
        EXPECT_FALSE(p_1.check_if_win(4,4));
        EXPECT_FALSE(p_1.check_if_win(1,0));
    }
    {
        // check diagonal down - top ⤢
        Player p_1(2, false);
        p_1.add_token(0,6);
        p_1.add_token(1,5);
        p_1.add_token(2,4);
        p_1.add_token(3,3);
        EXPECT_TRUE(p_1.check_if_win(0,6));
        EXPECT_TRUE(p_1.check_if_win(3,3));
        EXPECT_TRUE(p_1.check_if_win(2,4));
        EXPECT_FALSE(p_1.check_if_win(0,5));
        EXPECT_FALSE(p_1.check_if_win(1,6));
        EXPECT_FALSE(p_1.check_if_win(6,6));
    }
    {
        // check horizontal ⟷
        Player p_1(2, false);
        p_1.add_token(3,3);
        p_1.add_token(2,3);
        p_1.add_token(4,3);
        p_1.add_token(5,3);
        EXPECT_TRUE(p_1.check_if_win(3,3));
        EXPECT_TRUE(p_1.check_if_win(2,3));
        EXPECT_TRUE(p_1.check_if_win(5,3));
        EXPECT_FALSE(p_1.check_if_win(6,3));
        EXPECT_FALSE(p_1.check_if_win(1,3));
    }
    {
        // check vertical ↕
        Player p_1(2, false);
        p_1.add_token(3,3);
        p_1.add_token(3,4);
        p_1.add_token(3,5);
        p_1.add_token(3,2);
        EXPECT_TRUE(p_1.check_if_win(3,3));
        EXPECT_TRUE(p_1.check_if_win(3,2));
        EXPECT_TRUE(p_1.check_if_win(3,5));
        EXPECT_FALSE(p_1.check_if_win(3,6));
        EXPECT_FALSE(p_1.check_if_win(3,1));
        EXPECT_FALSE(p_1.check_if_win(4,6));
    }
}



TEST(PlayerTest, CheckWinTestFunction){
    {
        Player p_1(2, false);
        EXPECT_THROW(p_1.check_if_win_test(-1,0), invalid_argument);
        EXPECT_THROW(p_1.check_if_win_test(0,-1), invalid_argument);
        EXPECT_THROW(p_1.check_if_win_test(8,0), invalid_argument);
        EXPECT_THROW(p_1.check_if_win_test(0,8), invalid_argument);
    }

    {
        // check diagonal top - down ⤡
        Player p_1(2, false);
        p_1.add_token(1,1);
        p_1.add_token(2,2);
        p_1.add_token(3,3);
        EXPECT_TRUE(p_1.check_if_win_test(0,0));
        EXPECT_TRUE(p_1.check_if_win_test(4,4));
        EXPECT_FALSE(p_1.check_if_win_test(1,0));
    }
    {
        // check diagonal down - top ⤢
        Player p_1(2, false);
        p_1.add_token(1,5);
        p_1.add_token(2,4);
        p_1.add_token(3,3);
        EXPECT_TRUE(p_1.check_if_win_test(0,6));
        EXPECT_FALSE(p_1.check_if_win_test(3,3));
        EXPECT_TRUE(p_1.check_if_win_test(4,2));
        EXPECT_FALSE(p_1.check_if_win_test(1,6));
    }
    {
        // check horizontal ⟷
        Player p_1(2, false);
        p_1.add_token(3,3);
        p_1.add_token(4,3);
        p_1.add_token(5,3);
        EXPECT_TRUE(p_1.check_if_win_test(2,3));
        EXPECT_FALSE(p_1.check_if_win_test(3,3));
        EXPECT_TRUE(p_1.check_if_win_test(6,3));
        EXPECT_FALSE(p_1.check_if_win_test(1,3));
    }
    {
        // check vertical ↕
        Player p_1(2, false);
        p_1.add_token(3,3);
        p_1.add_token(3,4);
        p_1.add_token(3,5);
        EXPECT_TRUE(p_1.check_if_win_test(3,2));
        EXPECT_TRUE(p_1.check_if_win_test(3,6));
        EXPECT_FALSE(p_1.check_if_win_test(3,4));
        EXPECT_FALSE(p_1.check_if_win_test(4,6));
    }
}