#ifndef COLOR_HPP
#define COLOR_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Color
{
private:
    
    sf::Color color_;

public:

    Color(){};

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha = 255);

    uint8_t get_r()
    {
        return color_.r;
    }
    uint8_t get_g()
    {
        return color_.g;
    }
    uint8_t get_b()
    {
        return color_.b;
    }
    uint8_t get_a()
    {
        return color_.a;
    }

    sf::Color &get_color_ref()
    {
        return color_;
    }

    void set_r(uint8_t r)
    {
        color_.r = r;
    }
    void set_g(uint8_t g)
    {
        color_.g = g;
    }
    void set_b(uint8_t b)
    {
        color_.b = b;
    }
    void set_a(uint8_t a)
    {
        color_.a = a;
    }
};

#endif