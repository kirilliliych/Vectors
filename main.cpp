#include <ctime>
#include "displaywindow.hpp"
#include "coordsys.hpp"
#include "vector.hpp"

int main()
{
    DisplayWindow vector_field(800, 600, "Vectors");
    Rectangle background{800, 600};
    background.set_position(0, 0);

    Color background_color{160, 160, 160};
    background.set_fill_color(&background_color);
    background.draw(&vector_field);

    CoordSys axes1{-100, -100, 100, 100, 
                    100,  550, 300, 350,
                    200,  450};

    Color behind_vector_color{232, 0, 0};

    Rectangle rotating_vector_background{200, 200};
    rotating_vector_background.set_position(100, 50);
    rotating_vector_background.set_fill_color(&behind_vector_color);
    rotating_vector_background.draw(&vector_field);


    CoordSys axes2{-100, -100, 100, 100,
                    500,  550, 700, 350,
                    600,  450}; 
    axes2.set_vulnerability_to_clicks_mode(true);

    Rectangle moving_vector_background{200, 200};
    moving_vector_background.set_position(500, 50);
    moving_vector_background.set_fill_color(&behind_vector_color);
    moving_vector_background.draw(&vector_field);


    
    
    Vector seconds{0, 75};
    Vector minutes{0, 90};
    Vector hours  {0, 50};

    Color axes_color{0, 128, 0};
    Color vectors_color{255, 255, 255};

    Point point0{10, 10};

    hours.draw  (&vector_field, &axes1, &point0, &vectors_color);
    minutes.draw(&vector_field, &axes1, &point0, &vectors_color);
    seconds.draw(&vector_field, &axes1, &point0, &vectors_color);

    draw_coordsys(&vector_field, &axes1, &axes_color);
    draw_coordsys(&vector_field, &axes2, &axes_color);

    Vector moving_vector{30, 40};
    moving_vector.draw(&vector_field, &axes2, &point0, &vectors_color);

    vector_field.open();

    int time_passed = 0;
    while (vector_field.is_open())
    {
        vector_field.handle_events();

        vector_field.clear();
        vector_field.draw_objects();
        vector_field.display();

        rotate_vector(&seconds, SECONDS_AND_MINUTES_ARROW_ANGLE, 1);
        ++time_passed;
        if (time_passed % 60 == 0)
        {
            rotate_vector(&minutes, SECONDS_AND_MINUTES_ARROW_ANGLE, 0);
        }
        if (time_passed % 3600 == 0)
        {
            rotate_vector(&hours,   HOURS_ARROW_ANGLE, 0);
            time_passed = 0;
        }
    }

    return 0;
}