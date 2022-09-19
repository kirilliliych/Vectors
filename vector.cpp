#include "vector.hpp"
#include "displaywindow.hpp"
#include "coordsys.hpp"

// do destructors with poison

void Vector::draw(DisplayWindow *window, CoordSys *axes, Point *beginning, Color *color)
{
    assert(window    != nullptr);
    assert(axes      != nullptr);
    assert(beginning != nullptr);
    assert(color     != nullptr);
    
    window->add_drawable((Drawable *) this, axes, beginning, color);
}

Vector operator +(const Vector &opd1, const Vector &opd2)
{
    return Vector{opd1.get_x() + opd2.get_x(), opd1.get_y() + opd2.get_y()};
}

Vector operator -(const Vector &opd1, const Vector &opd2)
{
    return Vector{opd1.get_x() - opd2.get_x(), opd1.get_y() - opd2.get_y()};
}
