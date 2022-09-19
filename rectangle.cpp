#include "rectangle.hpp"
#include "displaywindow.hpp"

Rectangle::Rectangle(double x_size, double y_size)
{
    assert(std::isfinite(x_size));
    assert(std::isfinite(y_size));

    set_size(x_size, y_size);

    type_ = DrawableType::RECTANGLE;
}

Rectangle::Rectangle(Point *top_left_angle, Point *bottom_right_angle)
{
    assert(top_left_angle     != nullptr);
    assert(bottom_right_angle != nullptr);

    set_size(abs(bottom_right_angle->get_x() - top_left_angle->get_x()), 
             abs(top_left_angle->get_y()     - bottom_right_angle->get_y()));
    
    set_position(top_left_angle->get_x(), top_left_angle->get_y());

    type_ = DrawableType::RECTANGLE;
}

void Rectangle::set_size(double x_size, double y_size)
{
    assert(std::isfinite(x_size));
    assert(std::isfinite(y_size));

    sf::Vector2f size{(float) x_size, (float) y_size};

    rectangle_.setSize(size);
}

void Rectangle::set_position(double x_position, double y_position)
{
    assert(std::isfinite(x_position));
    assert(std::isfinite(y_position));

    rectangle_.setPosition(x_position, y_position);
}

void Rectangle::draw(DisplayWindow *window)
{
    assert(window != nullptr);

    window->add_drawable((uint8_t *) this, (CoordSys *) ABSENT_PTR_POISONED_VALUE, (Point *) ABSENT_PTR_POISONED_VALUE);
}