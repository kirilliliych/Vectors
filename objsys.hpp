#ifndef OBJSYS_HPP
#define OBJSYS_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "coordsys.hpp"
#include "point.hpp"
#include "color.hpp"


class ObjSys
{
public:

    Drawable *entity_    = nullptr;
    CoordSys *axes_      = nullptr;
    Point    *beginning_ = nullptr;
    Color    *color_     = nullptr;

    ObjSys(){};

    ObjSys(Drawable *entity, CoordSys *axes, Point *point, Color *color)
      : entity_(entity),
        axes_(axes),
        beginning_(point),
        color_(color)
    {}
};

#endif