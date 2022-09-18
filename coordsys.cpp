#include "coordsys.hpp"

CoordSys::CoordSys(double x_min, double y_min, 
                   double x_max, double y_max,
                   int x_area_rect_point1, int y_area_rect_point1,
                   int x_area_rect_point2, int y_area_rect_point2,
                   int x_origin_coord, int y_origin_coord)

      : x_min_coord_(x_min), 
        y_min_coord_(y_min), 
        x_max_coord_(x_max), 
        y_max_coord_(y_max)
{
    assert(std::isfinite(x_min));
    assert(std::isfinite(y_min));
    assert(std::isfinite(x_max));
    assert(std::isfinite(y_max));

    area_rect_point1_.set_x(x_area_rect_point1);
    area_rect_point1_.set_y(y_area_rect_point1);
    area_rect_point2_.set_x(x_area_rect_point2);
    area_rect_point2_.set_y(y_area_rect_point2);

    origin_point_.set_x(x_origin_coord);
    if (x_origin_coord == COORD_SYS_ORIGIN_FICTIVE_COORD_VALUE)
    {
        update_origin_x_position();
    }
    
    origin_point_.set_y(y_origin_coord);
    if (y_origin_coord == COORD_SYS_ORIGIN_FICTIVE_COORD_VALUE)
    {
        update_origin_y_position();
    }

    update_x_scale();
    update_y_scale();

    x_axis_.set_is_axis_vector(true);
    y_axis_.set_is_axis_vector(true);
}

void CoordSys::update_origin_x_position()
{
    origin_point_.set_x(abs(area_rect_point1_.get_x() - area_rect_point2_.get_x()) / 2 + 
                   std::min(area_rect_point1_.get_x(),  area_rect_point2_.get_x()));
}

void CoordSys::update_origin_y_position()
{
    origin_point_.set_y(abs(area_rect_point1_.get_y() - area_rect_point2_.get_y()) / 2 + 
                   std::min(area_rect_point1_.get_y(),  area_rect_point2_.get_y()));
}

void CoordSys::update_x_scale()
{
    int pixel_delta = abs(area_rect_point1_.get_x() - area_rect_point2_.get_x());

    x_scale_ = pixel_delta == 0 ? 0 : (x_max_coord_ - x_min_coord_) / pixel_delta;
}

void CoordSys::update_y_scale()
{
    int pixel_delta = abs(area_rect_point1_.get_y() - area_rect_point2_.get_y());
    
    y_scale_ = pixel_delta == 0 ? 0 : (y_max_coord_ - y_min_coord_) / pixel_delta;
}