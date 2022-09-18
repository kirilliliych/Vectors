#include "objsysarr.hpp"

void ObjSysArr::add(uint8_t *entity, CoordSys *axes, Point *beginning)
{
    assert(entity    != nullptr);
    assert(axes      != nullptr);
    assert(beginning != nullptr);

    assert(size_ <= OBJECTS_ON_THE_SCREEN_MAX_QUANTITY);

    array_[size_].entity_    = entity;
    array_[size_].axes_      = axes;
    array_[size_].beginning_ = beginning; 

    ++size_;
}