#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point{
    private:
    size_t x;
    size_t y;

    public:
    Point(size_t x=0, size_t y=0): x(x), y(y){}

    void set_x(size_t x){ this->x = x;};
    void set_y(size_t y){ this->y = y;};

    size_t get_x() const { return this->x; };
    size_t get_y() const { return this->y; };
};

#endif //POINT_H