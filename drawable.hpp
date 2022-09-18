#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


enum DrawableType
{
    VECTOR,
    UNKNOWN
};


class Drawable
{
protected:

    DrawableType type_ = DrawableType::UNKNOWN;

public:

    DrawableType get_drawable_type()
    {
        return type_;
    }
};

#endif