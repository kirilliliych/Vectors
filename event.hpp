#ifndef EVENT_HPP
#define EVENT_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


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

    sf::Keyboard::Key get_key_code()
    {
        return event_.key.code;
    }

    int get_mouse_click_x_position()
    {
        return event_.mouseButton.x;
    }
    int get_mouse_click_y_position()
    {
        return event_.mouseButton.y;
    }
};

#endif