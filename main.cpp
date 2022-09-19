#include <ctime>
#include "displaywindow.hpp"
#include "coordsys.hpp"
#include "vector.hpp"

int main()
{
    DisplayWindow vector_field(800, 600, "Vectors");
    // Rectangle screen{800, 600};
    // screen.set_position(0, 0);
    // screen.draw(&vector_field);

    CoordSys axes1{-100, -100, 100, 100, 
                    100,  550, 300, 350,
                    200,  450};

    CoordSys axes2{-100, -100, 100, 100,
                    500,  550, 700, 350,
                    600,  450}; 
    axes2.set_vulnerability_to_clicks_mode(true);
    
    Vector seconds{0, 75};
    Vector minutes{0, 90};
    Vector hours  {0, 50};

    Point point0{10, 10};

    vector_field.open();
    hours.draw  (&vector_field, &axes1, &point0);
    minutes.draw(&vector_field, &axes1, &point0);
    seconds.draw(&vector_field, &axes1, &point0);

    draw_coordsys(&vector_field, &axes1);
    draw_coordsys(&vector_field, &axes2);

    Vector jumping_vector{30, 40};
    jumping_vector.draw(&vector_field, &axes2, &point0);

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