#ifndef POINT_HPP
#define POINT_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Point
{
private:
    
    double x_ = 0;
    double y_ = 0;

public:

    Point(){}

    Point(double x, double y)
      : x_(x),
        y_(y)
    {
        assert(std::isfinite(x_));
        assert(std::isfinite(y_));   
    }

    double get_x() const
    {
        return x_;
    }
    double get_y() const
    {
        return y_;
    }

    void set_x(double x)
    {
        x_ = x;
    }
    void set_y(double y)
    {
        y_ = y;
    }
};

#endif