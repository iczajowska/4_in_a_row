#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "point.h"

using namespace sf;

class Token{
    private:
    Point point;
    Color color;
    CircleShape circle;

    public:
    Token(size_t player_id, Point p );
    Token(size_t player_id, size_t x, size_t y);
    
    Color get_token_color(){ return this->color; }
    Point get_point(){ return this->point; }
    bool operator==(const Token &other) const{ return (point.get_x()== other.point.get_x())&& (point.get_y()==other.point.get_y());}
    bool operator<(const Token &other) const { return point.get_x()<other.point.get_x() || (point.get_x() == other.point.get_x() && point.get_y()<other.point.get_y());}
    
    void display(RenderWindow &window, float start_x, float start_y, size_t num_of_col, float col_seperate_width, float radius, float outlineThickness) ;
    
};

#endif //TOKEN_H