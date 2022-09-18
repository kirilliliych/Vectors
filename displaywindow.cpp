#include "displaywindow.hpp"

DisplayWindow::DisplayWindow(int window_width, 
                             int window_height, 
                             const char *window_name)
      : window_width_ (window_width),
        window_height_(window_height)
{
    assert(window_width  > 0);
    assert(window_height > 0);
    assert(window_name != nullptr);

    strncpy(window_name_, window_name, MAX_WINDOW_NAME_LENGTH);
}

void DisplayWindow::create(int window_width,
                           int window_height,
                           const char *window_name)
{
    assert(window_name != nullptr);

    DisplayWindow(window_width, window_height, window_name);

    window_.create(sf::VideoMode(window_width, window_height), window_name);
}

void DisplayWindow::open()
{
    window_.create(sf::VideoMode(window_width_, window_height_), window_name_);
}

bool DisplayWindow::is_open()
{
    return window_.isOpen();
}

void DisplayWindow::close()
{
    window_.close();
}

bool DisplayWindow::poll_event(Event *event)
{
    assert(event != nullptr);

    return window_.pollEvent(event->get_event_ref());
}

void DisplayWindow::handle_events()
{
    Event event;
    while (poll_event(&event))
    {
        switch (event.get_event_type())
        {
            case sf::Event::Closed:
            {
                close();

                break;
            }
            
            case sf::Event::KeyPressed:
            {
                if (event.get_key_code() == sf::Keyboard::Escape)
                {
                    close();
                }

                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                Pixel mouse_click_position{event.get_mouse_click_x_position(), window_height_ - event.get_mouse_click_y_position()};
                for (size_t obj_index = 0; obj_index < object_buffer_.size_; ++obj_index)
                {
                    Drawable *drawable_type_ptr = (Drawable *) object_buffer_.array_[obj_index].entity_;
                    CoordSys *cur_axes = object_buffer_.array_[obj_index].axes_;
                    switch (drawable_type_ptr->get_drawable_type())
                    {
                        case DrawableType::VECTOR:
                        {
                            Vector *vector = (Vector *) drawable_type_ptr;
                            if ((!vector->get_is_axis_vector())                &&
                                (cur_axes->get_vulnerability_to_clicks_mode()) &&
                                (is_in_rectangle(&mouse_click_position, cur_axes->get_left_top_border_coords(),
                                                                        cur_axes->get_right_bottom_border_coords())))
                            {
                                int new_vector_x_pixel_coord = mouse_click_position.get_x() - cur_axes->get_x_origin();
                                int new_vector_y_pixel_coord = mouse_click_position.get_y() - cur_axes->get_y_origin();

                                
                                vector->set_x(new_vector_x_pixel_coord * cur_axes->get_x_scale());
                                vector->set_y(new_vector_y_pixel_coord * cur_axes->get_y_scale());
                            }
                            break;
                        }

                        default:
                        {
                            break;
                        }
                    }

                    
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }
}

void DisplayWindow::add_drawable(uint8_t *entity, CoordSys *axes, Point *beginning)
{
    assert(entity    != nullptr);
    assert(axes      != nullptr);
    assert(beginning != nullptr);

    object_buffer_.add(entity, axes, beginning);
}

void DisplayWindow::clear()
{
    window_.clear();
}

void DisplayWindow::display()
{
    window_.display();
}

void DisplayWindow::draw_vector(sf::Vertex *vector)
{
    assert(vector != nullptr);
    
    window_.draw(vector,     2, sf::Lines);
    window_.draw(vector + 1, 2, sf::Lines);
    window_.draw(vector + 3, 2, sf::Lines);
}

void DisplayWindow::draw_single_object(ObjSys *object_system_to_draw)
{
    Drawable *drawable_type_ptr = (Drawable *) object_system_to_draw->entity_;                   //  Base class Drawable contains variable type_ of type Drawable
                                                                                                 //  and all primitives (e.g. vectors) derive from him, therefore
                                                                                                 //  first sizeof(Drawable) bytes contain type_ variable
    switch (drawable_type_ptr->get_drawable_type())
    {
        case DrawableType::VECTOR:
        {
            sf::Vertex vector[VECTOR_ANCHOR_POINTS] = {};

            if (form_vector(object_system_to_draw, vector, this))
            {
                draw_vector(vector);
            }

            break;
        }

        case DrawableType::UNKNOWN:
        {
            std::cout << "Object with unknown type requires drawing" << std::endl;

            break;
        }
    }
}

void DisplayWindow::draw_objects()
{
    for (size_t obj_index = 0; obj_index < object_buffer_.size_; ++obj_index)
    {   
        draw_single_object(&object_buffer_.array_[obj_index]);
    }
}

int DisplayWindow::get_width()
{
    return window_width_;
}
int DisplayWindow::get_height()
{
    return window_height_;  
}