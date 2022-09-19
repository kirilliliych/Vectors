#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "point.hpp"
#include "drawable.hpp"
#include "utilities.hpp"


class DisplayWindow;


class Rectangle : public Drawable
{
private:

    sf::RectangleShape rectangle_{};

public:

    Rectangle()
    {
        type_ = DrawableType::RECTANGLE;
    }

    Rectangle(double x_size, double y_size);

    Rectangle(Point *top_left_angle, Point *bottom_right_angle);

    const sf::RectangleShape *get_rectangle_ptr()
    {
        return &rectangle_;
    }

    void set_size(double x_size, double y_size);

    void set_position(double x_position, double y_position);

    void draw(DisplayWindow *window);
};


#endif