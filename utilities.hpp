#ifndef UTILITIES_HPP
#define UTILITIES_HPP


#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "point.hpp"
#include "vector.hpp"
#include "objsys.hpp"
#include "event.hpp"


const double DOUBLE_COMPARISON_PRECISION = 0.001;

static const void *ABSENT_PTR_POISONED_VALUE = (const void *) 0xDEADBEEF;


bool is_in_rectangle(const Point *point, const Point *rect_angle1, const Point *rect_angle2);

bool is_in_rectangle(const Pixel *point, const Pixel *rect_angle1, const Pixel *rect_angle2);

void multiply_vector(Vector *vector, double multiplier);

double get_vector_length_square(Vector *vector);

void normalize_vector(Vector *vector);

void set_vector_length(Vector *vector, double length);

bool form_line(ObjSys *object_system_to_draw, sf::Vertex *line, DisplayWindow *window); // make draw_line?

void form_arrow(ObjSys *object_system_to_draw, sf::Vertex *vector, DisplayWindow *window);

bool form_vector(ObjSys *object_system_to_draw, sf::Vertex *vector, DisplayWindow *window);

void rotate_vector(Vector *vector_to_rotate, double angle, double seconds_to_sleep);

void sleep(double seconds);

void process_clickable_entities(DisplayWindow *window, Pixel *mouse_click_position);

void process_clickable_vector(DisplayWindow *window, Vector *vector, CoordSys *axes, 
                              Point *beginnning, Pixel *mouse_click_position);

void draw_coordsys(DisplayWindow *window, CoordSys *axes);

void event_close(DisplayWindow *window);

void event_key_pressed(DisplayWindow *window, Event *event);

void event_mouse_button_pressed(DisplayWindow *window, Event *event);


#endif