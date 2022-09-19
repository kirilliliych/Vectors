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


class ObjSys
{
public:

    uint8_t  *entity_    = nullptr;
    CoordSys *axes_      = nullptr;
    Point    *beginning_ = nullptr;

    ObjSys(){};

    ObjSys(uint8_t *entity, CoordSys *axes, Point *point)
      : entity_(entity),
        axes_(axes),
        beginning_(point) 
    {}
};

#endif