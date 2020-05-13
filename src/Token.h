#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Point.h"

using namespace sf;

class Token{
    private:
    Point point;
    Color color;
    CircleShape circle;


    public:
    Token(size_t player_id, Point p ) {
        this->point = p;
        if(player_id==1){
            color = Color::Yellow;
        } else{
            color = Color::Red;
        }
    }

    Token(size_t player_id, size_t x, size_t y){
        Point p= Point(x,y);
        this->point = p;
        if(player_id==1){
            color = Color::Yellow;
        } else{
            color = Color::Red;
        }

    }

    Color get_token_color(){
        return this->color;
    }
    Point get_point(){
        return this->point;
    }


    bool operator==(const Token &other) const{
        return (point.get_x()== other.point.get_x())&& (point.get_y()==other.point.get_y());
        //return std::hypot(point.get_x(),point.get_y())< std::hypot(other.point.get_x(), other.point.get_y());
    
    }

    bool operator<(const Token &other) const {
        return point.get_x()<other.point.get_x() || (point.get_x() == other.point.get_x() && point.get_y()<other.point.get_y());
    }
    void display(RenderWindow &window, float start_x, float start_y, size_t num_of_col, float col_seperate_width, float radius, float outlineThickness) {
        float x = start_x+ float(point.get_x())*(radius*2+col_seperate_width)  + col_seperate_width;
        float y = start_y + float(point.get_y())*(radius*2+col_seperate_width) + col_seperate_width;
        //std::cout<<"Token display: "<<x<<" "<<y<<" col start: "<<x-radius<<"end: "<<x+radius<<"\n";
        circle.setPosition(x,y);
        circle.setRadius(radius);
        circle.setFillColor(color);
        circle.setOutlineColor(Color(85,79,167));
        circle.setOutlineThickness(outlineThickness);
        window.draw(circle);
    }
    
};

#endif //TOKEN_H