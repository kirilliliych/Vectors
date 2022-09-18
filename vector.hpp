#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "point.hpp"

class CoordSys;
class DisplayWindow;

const size_t VECTOR_ANCHOR_POINTS = 5;

const int VECTOR_ARROW_PARALLEL_COMPONENT_SQRT_PIXEL_LENGTH = 15;
const int VECTOR_ARROW_SIDE_COMPONENT_SQRT_PIXEL_LENGTH     = 8;

const double SECONDS_AND_MINUTES_ARROW_ANGLE = -0.08727;
const double HOURS_ARROW_ANGLE               = -0.5236;


class Vector : public Drawable
{
private:

    double x_coord_ = 0;
    double y_coord_ = 0;
    
    bool is_axis_vector_ = false;

public:
    
    Vector()
    {
        type_ = DrawableType::VECTOR;
    }

    Vector(double x_coord, double y_coord)
      : x_coord_(x_coord),
        y_coord_(y_coord)
    {
        assert(std::isfinite(x_coord));
        assert(std::isfinite(y_coord));

        type_ = DrawableType::VECTOR;
    }

    double get_x() const
    {
        return x_coord_;
    }
    double get_y() const
    {
        return y_coord_;
    }
    bool get_is_axis_vector()
    {
        return is_axis_vector_;
    }

    void set_x(double x)
    {
        x_coord_ = x;
    }
    void set_y(double y)
    {
        y_coord_ = y;
    }
    void set_is_axis_vector(bool is_axis_vector)
    {
        is_axis_vector_ = is_axis_vector;
    }

    void draw(DisplayWindow *window, CoordSys *axes, Point *beginning); 
};


Vector operator +(const Vector &opd1, const Vector &opd2);

Vector operator -(const Vector &opd1, const Vector &opd2);

#endif
