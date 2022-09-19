#ifndef OBJSYSARR_HPP
#define OBJSYSARR_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "objsys.hpp"


const size_t OBJECTS_ON_THE_SCREEN_MAX_QUANTITY = 1024;


class ObjSysArr
{   
public:

    ObjSysArr(){};

    ObjSys array_[OBJECTS_ON_THE_SCREEN_MAX_QUANTITY];
    size_t size_ = 0;

    void add(Drawable *entity, CoordSys *axes, Point *beginning, Color *color);
};

#endif