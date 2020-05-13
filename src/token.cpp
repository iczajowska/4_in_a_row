#include "token.h"
Token::Token(size_t player_id, Point p ) {
    this->point = p;
    if(player_id==1){
        color = Color::Yellow;
    } else{
        color = Color::Red;
    }
}

Token::Token(size_t player_id, size_t x, size_t y){
    Point p= Point(x,y);
    this->point = p;
    if(player_id==1){
        color = Color::Yellow;
    } else{
        color = Color::Red;
    }

}

void Token::display(RenderWindow &window, float start_x, float start_y, size_t num_of_col, float col_seperate_width, float radius, float outlineThickness) {
    float x = start_x+ float(point.get_x())*(radius*2+col_seperate_width)  + col_seperate_width;
    float y = start_y + float(point.get_y())*(radius*2+col_seperate_width) + col_seperate_width;
    circle.setPosition(x,y);
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setOutlineColor(Color(85,79,167));
    circle.setOutlineThickness(outlineThickness);
    window.draw(circle);
}