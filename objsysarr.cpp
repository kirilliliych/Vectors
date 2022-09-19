#include "objsysarr.hpp"


void ObjSysArr::add(Drawable *entity, CoordSys *axes, Point *beginning, Color *color)
{
    assert(entity    != nullptr);
    assert(axes      != nullptr);
    assert(beginning != nullptr);
    assert(color     != nullptr);

    assert(size_ <= OBJECTS_ON_THE_SCREEN_MAX_QUANTITY);

    array_[size_].entity_    = entity;
    array_[size_].axes_      = axes;
    array_[size_].beginning_ = beginning; 
    array_[size_].color_     = color;

    ++size_;
}