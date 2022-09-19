#include "utilities.hpp"
#include "displaywindow.hpp"

bool is_in_rectangle(const Point *point, const Point *rect_angle1, const Point *rect_angle2)
{
    assert(point       != nullptr);
    assert(rect_angle1 != nullptr);
    assert(rect_angle2 != nullptr);

    return ((rect_angle1->get_x() - DOUBLE_COMPARISON_PRECISION < point->get_x()) && (point->get_x() < rect_angle2->get_x() + DOUBLE_COMPARISON_PRECISION) &&
            (rect_angle1->get_y() - DOUBLE_COMPARISON_PRECISION < point->get_y()) && (point->get_y() < rect_angle2->get_y() + DOUBLE_COMPARISON_PRECISION))
    ? true : false;
}

bool is_in_rectangle(const Pixel *point, const Pixel *rect_angle1, const Pixel *rect_angle2)
{
    assert(point       != nullptr);
    assert(rect_angle1 != nullptr);
    assert(rect_angle2 != nullptr);

    return ((rect_angle1->get_x() <= point->get_x()) && (point->get_x() <= rect_angle2->get_x()) &&
            (rect_angle2->get_y() <= point->get_y()) && (point->get_y() <= rect_angle1->get_y()))
    ? true : false;
}

void multiply_vector(Vector *vector, double multiplier)
{
    assert(vector != nullptr);
    assert(std::isfinite(multiplier));

    vector->set_x(vector->get_x() * multiplier);
    vector->set_y(vector->get_y() * multiplier);
}

double get_vector_length_square(Vector *vector)
{
    assert(vector != nullptr);

    return vector->get_x() * vector->get_x() + vector->get_y() * vector->get_y();
}

void normalize_vector(Vector *vector)
{
    assert(vector != nullptr);

    double denominator = get_vector_length_square(vector);
    assert(denominator != 0);

    vector->set_x(vector->get_x() / sqrt(denominator));
    vector->set_y(vector->get_y() / sqrt(denominator));
}

void set_vector_length(Vector *vector, double length)
{
    assert(vector != nullptr);

    normalize_vector(vector);
    multiply_vector (vector, length);
}

bool form_line(ObjSys *object_system_to_draw, sf::Vertex *line, DisplayWindow *window)
{
    assert(object_system_to_draw != nullptr);
    assert(line                  != nullptr);
    assert(window                != nullptr);

    Vector *vector_to_draw = (Vector *) object_system_to_draw->entity_;
    double x_beginning = object_system_to_draw->beginning_->get_x();
    double y_beginning = object_system_to_draw->beginning_->get_y();
    double x_ending    = object_system_to_draw->beginning_->get_x() + vector_to_draw->get_x();
    double y_ending    = object_system_to_draw->beginning_->get_y() + vector_to_draw->get_y();

    Point rect_angle1{object_system_to_draw->axes_->get_x_min(), object_system_to_draw->axes_->get_y_min()};
    Point rect_angle2{object_system_to_draw->axes_->get_x_max(), object_system_to_draw->axes_->get_y_max()};
    Point beginning{x_beginning, y_beginning};
    Point ending   {x_ending,    y_ending};
    
    if ((!is_in_rectangle(&beginning, &rect_angle1, &rect_angle2)) ||
        (!is_in_rectangle(&ending,    &rect_angle1, &rect_angle2)))
    {
        return false;
    }

    line[0].position.x = (int) (x_beginning * object_system_to_draw->axes_->get_x_scale() + object_system_to_draw->axes_->get_x_origin());
    line[1].position.x = (int) (x_ending    * object_system_to_draw->axes_->get_x_scale() + object_system_to_draw->axes_->get_x_origin());
    line[0].position.y = window->get_height() - (int) (y_beginning * object_system_to_draw->axes_->get_y_scale()) - object_system_to_draw->axes_->get_y_origin();
    line[1].position.y = window->get_height() - (int) (y_ending    * object_system_to_draw->axes_->get_y_scale()) - object_system_to_draw->axes_->get_y_origin();

    return true;
}

void form_arrow(ObjSys *object_system_to_draw, sf::Vertex *vector, DisplayWindow *window)
{
    assert(object_system_to_draw != nullptr);
    assert(vector                != nullptr);
    assert(window                != nullptr);

    Vector parallel_component{((Vector *) (object_system_to_draw->entity_))->get_x() * (-1),
                              ((Vector *) (object_system_to_draw->entity_))->get_y() * (-1)};
    set_vector_length(&parallel_component, VECTOR_ARROW_PARALLEL_COMPONENT_SQRT_PIXEL_LENGTH);

    Vector first_side_component{((Vector *) (object_system_to_draw->entity_))->get_y() * (-1), 
                                ((Vector *) (object_system_to_draw->entity_))->get_x()};
    set_vector_length(&first_side_component, VECTOR_ARROW_SIDE_COMPONENT_SQRT_PIXEL_LENGTH);

    Vector second_side_component{((Vector *) (object_system_to_draw->entity_))->get_y(), 
                                 ((Vector *) (object_system_to_draw->entity_))->get_x() * (-1)};
    set_vector_length(&second_side_component, VECTOR_ARROW_SIDE_COMPONENT_SQRT_PIXEL_LENGTH);

    Vector first_wing  = parallel_component + first_side_component;
    Vector second_wing = parallel_component + second_side_component;

    vector[2].position.x = vector[1].position.x + first_wing.get_x();
    vector[2].position.y = vector[1].position.y - first_wing.get_y();

    vector[3].position.x = vector[1].position.x;
    vector[3].position.y = vector[1].position.y;

    vector[4].position.x = vector[3].position.x + second_wing.get_x();
    vector[4].position.y = vector[3].position.y - second_wing.get_y();
}

bool form_vector(ObjSys *object_system_to_draw, sf::Vertex *vector, DisplayWindow *window)
{
    assert(object_system_to_draw != nullptr);
    assert(vector                != nullptr);
    assert(window                != nullptr);

    if (!form_line(object_system_to_draw, vector, window))
    {
        return false;
    }

    form_arrow(object_system_to_draw, vector, window);
    
    return true;
}

void rotate_vector(Vector *vector_to_rotate, double angle, double seconds_to_sleep)
{
    assert(vector_to_rotate != nullptr);
    assert(std::isfinite(angle));
    
    double sin = std::sin(angle);
    double cos = std::cos(angle);

    double new_x = vector_to_rotate->get_x() * cos + vector_to_rotate->get_y() * (-sin);
    double new_y = vector_to_rotate->get_x() * sin + vector_to_rotate->get_y() *   cos;
    
    double vector_prev_length = sqrt(get_vector_length_square(vector_to_rotate));

    vector_to_rotate->set_x(new_x);
    vector_to_rotate->set_y(new_y);

    normalize_vector(vector_to_rotate);
    set_vector_length(vector_to_rotate, vector_prev_length);

    sleep(sf::seconds(seconds_to_sleep));
}

void sleep(double seconds)
{
    assert(std::isfinite(seconds));

    sf::sleep(sf::seconds(seconds));
}

void draw_coordsys(DisplayWindow *window, CoordSys *axes)
{
    assert(window != nullptr);
    assert(axes   != nullptr);

    axes->x_axis_.set_x(abs(axes->get_x_max() - axes->get_x_min()));
    axes->x_axis_.set_y(0);
    axes->y_axis_.set_x(0);
    axes->y_axis_.set_y(abs(axes->get_y_max() - axes->get_y_min()));
    
    axes->x_axis_beginning_.set_x(axes->get_x_min());
    axes->x_axis_beginning_.set_y(0);
    axes->y_axis_beginning_.set_x(0);
    axes->y_axis_beginning_.set_y(axes->get_y_min());

    axes->x_axis_.draw(window, axes, &axes->x_axis_beginning_);
    axes->y_axis_.draw(window, axes, &axes->y_axis_beginning_);
}

void event_close(DisplayWindow *window)
{
    assert(window != nullptr);

    window->close();
}

void event_key_pressed(DisplayWindow *window, Event *event)
{
    assert(window != nullptr);
    assert(event  != nullptr);

    if (event->get_key_code() == sf::Keyboard::Escape)
    {
        window->close();
    }
}

void event_mouse_button_pressed(DisplayWindow *window, Event *event)
{
    assert(window != nullptr);
    assert(event  != nullptr);

    Pixel mouse_click_position{event->get_mouse_click_x_position(), window->get_height() - event->get_mouse_click_y_position()};

    process_clickable_entities(window, &mouse_click_position);
}

void process_clickable_entities(DisplayWindow *window, Pixel *mouse_click_position)
{
    assert(window               != nullptr);
    assert(mouse_click_position != nullptr);

    for (size_t obj_index = 0; obj_index < window->get_object_buffer()->size_; ++obj_index)
    {
        Drawable *cur_entity = (Drawable *) window->get_object_buffer()->array_[obj_index].entity_;
        CoordSys *cur_axes   =              window->get_object_buffer()->array_[obj_index].axes_;
        Point    *beginning  =              window->get_object_buffer()->array_[obj_index].beginning_;

        switch (cur_entity->get_drawable_type())
        {
            case DrawableType::VECTOR:
            {
                process_clickable_vector(window, (Vector *) cur_entity, cur_axes, beginning, mouse_click_position);
                
                break;
            }

            default:
            {
                break;
            }
        }   
    }
}

void process_clickable_vector(DisplayWindow *window, Vector *vector, CoordSys *axes, 
                              Point *beginning, Pixel *mouse_click_position)
{
    assert(window               != nullptr);
    assert(vector               != nullptr);
    assert(axes                 != nullptr);
    assert(beginning            != nullptr);
    assert(mouse_click_position != nullptr);

    if ((!vector->get_is_axis_vector())            &&
        (axes->get_vulnerability_to_clicks_mode()) &&
        (is_in_rectangle(mouse_click_position, axes->get_top_left_border_coords(),
                                               axes->get_bottom_right_border_coords())))
    {
        int beginning_x_pixel_coord  = beginning->get_x() * axes->get_x_scale();
        int beginning_y_pixel_coord  = beginning->get_y() * axes->get_y_scale();
        int new_vector_x_pixel_coord = mouse_click_position->get_x() - (beginning_x_pixel_coord + axes->get_x_origin());
        int new_vector_y_pixel_coord = mouse_click_position->get_y() - (beginning_y_pixel_coord + axes->get_y_origin());

        assert(axes->get_x_scale() != 0);
        assert(axes->get_y_scale() != 0);
        vector->set_x(new_vector_x_pixel_coord / axes->get_x_scale());
        vector->set_y(new_vector_y_pixel_coord / axes->get_y_scale());
    }
}