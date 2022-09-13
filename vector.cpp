#include "vector.hpp"
#include "sizes.hpp"

#define aboba std::cout << "aboba " << __LINE__ << std::endl;

// do destructors with poison

class Point
{
private:
    
    double x_ = 0;
    double y_ = 0;

public:

    Point(){}

    Point(double x, double y)
      : x_(x),
        y_(y)
    {
        assert(std::isfinite(x_));
        assert(std::isfinite(y_));   
    }

    double get_x()
    {
        return x_;
    }
    double get_y()
    {
        return y_;
    }

    void set_x(double x)
    {
        x_ = x;
    }
    void set_y(double y)
    {
        y_ = y;
    }
};

class Pixel
{
private:
    
    int x_ = 0;
    int y_ = 0;

public:

    Pixel(){}

    Pixel(int x, int y)
      : x_(x),
        y_(y)
    {}

    int get_x()
    {
        return x_;
    }
    int get_y()
    {
        return y_;
    }

    void set_x(int x)
    {
        x_ = x;
    }
    void set_y(int y)
    {
        y_ = y;
    }

    // void drawpixel?
};

class CoordSys                                          // внести примитивы в координатную систему(чтобы не пересчитывать все каждый раз)   // текст для подписи координат
{
private:

    double x_min_coord_ = 0;
    double y_min_coord_ = 0;
    double x_max_coord_ = 0;
    double y_max_coord_ = 0;
    
    Pixel area_rect_point_1_{};
    Pixel area_rect_point_2_{};
    Pixel origin_point_{};

    double x_scale_ = 0;
    double y_scale_ = 0;

    void update_origin_x_position();
    void update_origin_y_position();
    void update_x_scale();
    void update_y_scale();

public:

    CoordSys(){}

    CoordSys(double x_min, double y_min,
             double x_max, double y_max,
             int x_area_rect_point_1, int y_area_rect_point_1,
             int x_area_rect_point_2, int y_area_rect_point_2);

    double get_x_min()
    {
        return x_min_coord_;
    }
    double get_y_min()
    {
        return y_min_coord_;
    }
    double get_x_max()
    {
        return x_max_coord_;
    }
    double get_y_max()
    {
        return y_max_coord_;
    }
    double get_x_scale()
    {
        return x_scale_;
    }
    double get_y_scale()
    {
        return y_scale_;
    }

    void set_x_min(double x_min) // for changing coords? resize?
    {
        x_min_coord_ = x_min;
    }
    void set_y_min(double y_min)
    {
        y_min_coord_ = y_min;
    }
    void set_x_max(double x_max)
    {
        x_max_coord_ = x_max;
    }
    void set_y_max(double y_max)
    {
        y_max_coord_ = y_max;
    }

    // TODO: do draw method to make coordsys visible in the window
}; 

class Event
{
private:

    sf::Event event_{};

public:

    sf::Event get_event()
    {
        return event_;
    }
    sf::Event &get_event_ref()                  //
    {                                           //
        return event_;                          //  required because SFML's function pollEvent requires a reference to the Event class member
    }                                           //

    void set_event(sf::Event event)
    {
        event_ = event;
    }

    sf::Event::EventType get_event_type()
    {
        return event_.type;
    }
};

/********************************************************************************/
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
/********************************************************************************/

class Vector : public Drawable
{
private:

    double x_coord_ = 0;
    double y_coord_ = 0;

    int arrow_wings_length_ = 0;

    
public:
    
    Vector()
    {
        type_ = DrawableType::VECTOR;
    }

    Vector(double x_coord, double y_coord)
      : x_coord_(x_coord),
        y_coord_(y_coord)
    {
        assert(std::isfinite(x_coord));
        assert(std::isfinite(y_coord));

        type_ = DrawableType::VECTOR;
    }

    double get_x()
    {
        return x_coord_;
    }
    double get_y()
    {
        return y_coord_;
    }

    DrawableType get_drawable_type()
    {
        return type_;
    }

    void set_x(double x)
    {
        x_coord_ = x;
    }
    void set_y(double y)
    {
        y_coord_ = y;
    }

    void draw(DisplayWindow *window, CoordSys *axes, Point *beginning); 
};


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

class ObjSysArr
{   
public:

    ObjSysArr(){};

    ObjSys array_[OBJECTS_ON_THE_SCREEN_MAX_QUANTITY];
    size_t size_ = 0;

    void add(uint8_t *entity, CoordSys *axes, Point *beginning);
    // erase? make a list of free places to fill emptys after erasing? remember place in array in vector to erase properly and to update if it was changed? 
};

class DisplayWindow
{
private:

    int window_width_  = 0;
    int window_height_ = 0;

    ObjSysArr object_buffer_{};

    char window_name_[MAX_WINDOW_NAME_LENGTH] = {};

    sf::RenderWindow window_{};

    bool redraw_required_flag_ = false;
    
public:

    DisplayWindow();

    DisplayWindow(int window_width  = STANDARD_WINDOW_WIDTH, 
                  int window_height = STANDARD_WINDOW_HEIGHT, 
                  const char *window_name = STANDARD_WINDOW_NAME);
    
    void create(int window_width  = STANDARD_WINDOW_WIDTH,
                int window_height = STANDARD_WINDOW_HEIGHT,
                const char *window_name = STANDARD_WINDOW_NAME);

    void open();

    bool is_open();

    bool poll_event(Event *event);

    void close();

    void handle_events();

    void update_display();

    void add_drawable(uint8_t *entity, CoordSys *axis, Point *beginning);
    
    void handle_draw_requests();

    void clear();

    void display();

    void draw_single_object(ObjSys *object_to_draw);

    void draw_objects();

    void draw_vector(sf::Vertex *vector);

    int get_width();
    
    int get_height();

    void set_redraw_required_flag(bool redraw_flag);

    // TODO: resize with setters?
};


CoordSys::CoordSys(double x_min, double y_min, 
                   double x_max, double y_max,
                   int x_area_rect_point_1, int y_area_rect_point_1,
                   int x_area_rect_point_2, int y_area_rect_point_2)

      : x_min_coord_(x_min), 
        y_min_coord_(y_min), 
        x_max_coord_(x_max), 
        y_max_coord_(y_max)
{
    assert(std::isfinite(x_min));
    assert(std::isfinite(y_min));
    assert(std::isfinite(x_max));
    assert(std::isfinite(y_max));

    area_rect_point_1_.set_x(x_area_rect_point_1);
    area_rect_point_1_.set_y(y_area_rect_point_1);
    area_rect_point_2_.set_x(x_area_rect_point_2);
    area_rect_point_2_.set_y(y_area_rect_point_2);

    update_origin_x_position();
    update_origin_y_position();

    update_x_scale();
    update_y_scale();
}

void CoordSys::update_origin_x_position()
{
    origin_point_.set_x(abs(area_rect_point_1_.get_x() - area_rect_point_2_.get_x()) / 2 + 
                   std::min(area_rect_point_1_.get_x(),  area_rect_point_2_.get_x()));
}

void CoordSys::update_origin_y_position()
{
    origin_point_.set_y(abs(area_rect_point_1_.get_y() - area_rect_point_2_.get_y()) / 2 + 
                   std::min(area_rect_point_1_.get_y(),  area_rect_point_2_.get_y()));
}

void CoordSys::update_x_scale()
{
    int pixel_delta = abs(area_rect_point_1_.get_x() - area_rect_point_2_.get_x());

    x_scale_ = pixel_delta == 0 ? 0 : (x_max_coord_ - x_min_coord_) / pixel_delta;
}

void CoordSys::update_y_scale()
{
    int pixel_delta = abs(area_rect_point_1_.get_y() - area_rect_point_2_.get_y());
    
    y_scale_ = pixel_delta == 0 ? 0 : (y_max_coord_ - y_min_coord_) / pixel_delta;
}

void Vector::draw(DisplayWindow *window, CoordSys *axes, Point *beginning)
{
    assert(window    != nullptr);
    assert(axes      != nullptr);
    assert(beginning != nullptr);
    
    window->add_drawable((uint8_t *) this, axes, beginning);
}

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
    
    window_.draw(vector, 2, sf::Lines);
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
            sf::Vertex vector[VECTOR_COMPONENTS] = {};

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


bool is_between(double left, double value, double right)
{
    assert(std::isfinite(left));
    assert(std::isfinite(value));
    assert(std::isfinite(right));

    return ((left - DOUBLE_COMPARISON_PRECISION <= value)   && 
            (value <= right + DOUBLE_COMPARISON_PRECISION)) ?
    true : false;
}

bool is_in_rectangle(Point *first, Point *rect_angle1, Point *rect_angle2)
{
    assert(first       != nullptr);
    assert(rect_angle1 != nullptr);
    assert(rect_angle2 != nullptr);

    return ((rect_angle1->get_x() - DOUBLE_COMPARISON_PRECISION < first->get_x()) && (first->get_x() < rect_angle2->get_x() + DOUBLE_COMPARISON_PRECISION) &&
            (rect_angle1->get_y() - DOUBLE_COMPARISON_PRECISION < first->get_y()) && (first->get_y() < rect_angle2->get_y() + DOUBLE_COMPARISON_PRECISION))
    ? true : false;
}

bool form_line(ObjSys *object_system_to_draw, sf::Vertex *line, DisplayWindow *window)
{
    assert(object_system_to_draw != nullptr);
    assert(line                  != nullptr);
    assert(window                != nullptr);

    Vector *vector_to_draw = (Vector *) object_system_to_draw->entity_;
    double x_beginning =  object_system_to_draw->beginning_->get_x();
    double y_beginning =  object_system_to_draw->beginning_->get_y();
    double x_ending    =  object_system_to_draw->beginning_->get_x() + vector_to_draw->get_x();
    double y_ending    =  object_system_to_draw->beginning_->get_y() + vector_to_draw->get_y();

    Point rect_angle1{object_system_to_draw->axes_->get_x_min(), object_system_to_draw->axes_->get_y_min()};
    Point rect_angle2{object_system_to_draw->axes_->get_x_max(), object_system_to_draw->axes_->get_y_max()};
    Point beginning{(double) x_beginning, (double) y_beginning};
    Point ending   {(double) x_ending,    (double) y_ending};

    // if ((!is_in_rectangle(&beginning, &rect_angle1, &rect_angle2)) || 
    //     (!is_in_rectangle(&ending,    &rect_angle1, &rect_angle2)));
    // {
    //     return false;
    // }

    line[0].position.x = (int) (x_beginning * object_system_to_draw->axes_->get_x_scale());
    line[1].position.x = (int) (x_ending    * object_system_to_draw->axes_->get_x_scale());
    line[0].position.y = window->get_height() - (int) (y_beginning * object_system_to_draw->axes_->get_y_scale());
    line[1].position.y = window->get_height() - (int) (y_ending    * object_system_to_draw->axes_->get_y_scale());

    return true;
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

    // form_wings

    return true;
}


int main()
{
    int window_width  = 0;
    int window_height = 0;
    std::cout << "Enter window width and window height in pixels, leaving space between these two values:" << std::endl;
    std::cin  >> window_width >> window_height;    

    char window_name[MAX_WINDOW_NAME_LENGTH + 1] = {};
    std::cout << "Enter window name:" << std::endl;
    scanf("%s31", window_name);

    DisplayWindow vector_field(window_width, window_height, window_name);
    CoordSys axes1{-100, -100, 100, 100, 0, 0, 400, 400};
    Vector v1{50.3, 35.5};
    Point point0{10, 10};
    Vector v2{-100, -200};
    Point point1{600, 300};

    vector_field.open();
    v1.draw(&vector_field, &axes1, &point0);
    // v2.draw(&vector_field, &axes1, &point1);
    
    while (vector_field.is_open())
    {
        vector_field.handle_events();

        vector_field.clear();
        vector_field.draw_objects();
        vector_field.display();
    }

    return 0;
}