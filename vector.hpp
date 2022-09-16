#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


enum DrawableType
{
    VECTOR,
    UNKNOWN
};


class Point;

class Pixel;

class CoordSys;

class Event;

class Drawable;

class Vector;

class DisplayWindow;

class DrawableElem;

class ObjSys;

class ObjSysArr;


const int COORD_SYS_ORIGIN_FICTIVE_COORD_VALUE  = -1337228;

const size_t MAX_WINDOW_NAME_LENGTH             = 31;
const size_t STANDARD_WINDOW_WIDTH              = 800;
const size_t STANDARD_WINDOW_HEIGHT             = 600;

const size_t OBJECTS_ON_THE_SCREEN_MAX_QUANTITY = 1024;

const char *STANDARD_WINDOW_NAME = "SFML Window";

const double DOUBLE_COMPARISON_PRECISION = 0.001;


bool is_in_rectangle(Point *point_to_check, Point *point_rect1, Point *point_rect2);

void multiply_vector(Vector *vector, double  multiplier);

double get_vector_length_square(Vector *vector);

void normalize_vector(Vector *vector);

void set_vector_length(Vector *vector, double length);

bool form_line  (ObjSys *object_system_to_draw, sf::Vertex *line,   DisplayWindow *window);

void form_arrow (ObjSys *object_system_to_draw, sf::Vertex *vector, DisplayWindow *window);

bool form_vector(ObjSys *object_system_to_draw, sf::Vertex *line,   DisplayWindow *window);

void rotate_vector(Vector *vector_to_rotate, double angle, sf::Time seconds_to_sleep);

Vector operator +(const Vector &opd1, const Vector &opd2);


#endif
