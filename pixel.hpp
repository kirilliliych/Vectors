#ifndef PIXEL_HPP
#define PIXEL_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Pixel
{
private:
    
    int x_ = 0;
    int y_ = 0;

public:

    Pixel(){}

    Pixel(int x, int y)
      : x_(x),
        y_(y)
    {}

    int get_x() const
    {
        return x_;
    }
    int get_y() const
    {
        return y_;
    }

    void set_x(int x)
    {
        x_ = x;
    }
    void set_y(int y)
    {
        y_ = y;
    }

    // void drawpixel?
};

#endif