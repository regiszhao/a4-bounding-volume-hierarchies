#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
	// find intersection of tx, ty, tz, and min_t to max_t
	double x_min = box.min_corner(0); double y_min = box.min_corner(1); double z_min = box.min_corner(2);
	double x_max = box.max_corner(0); double y_max = box.max_corner(1); double z_max = box.max_corner(2);
	double x_e = ray.origin(0); double y_e = ray.origin(1); double z_e = ray.origin(2);
	double x_d = ray.direction(0); double y_d = ray.direction(1); double z_d = ray.direction(2);

	// check x axis
	double tx_min = (x_min - x_e) / x_d;
	double tx_max = (x_max - x_e) / x_d;
	if (tx_min > tx_max) {
		std::swap(tx_min, tx_max);
	}

	// check y axis
	double ty_min = (y_min - y_e) / y_d;
	double ty_max = (y_max - y_e) / y_d;
	if (ty_min > ty_max) {
		std::swap(ty_min, ty_max);
	}

	// check z axis
	double tz_min = (z_min - z_e) / z_d;
	double tz_max = (z_max - z_e) / z_d;
	if (tz_min > tz_max) {
		std::swap(tz_min, tz_max);
	}

	// get t_min and t_max
	double t_min = std::max({ tx_min, ty_min, tz_min });
	double t_max = std::min({ tx_max, ty_max, tz_max });
	
	return (t_max >= min_t) && (t_min <= max_t);


	//double tx_min; double ty_min; double tz_min;
	//double tx_max; double ty_max; double tz_max;

	//// calculate range for x
	//if (x_d >= 0) {
	//	tx_min = (x_min - x_e) / x_d;
	//	tx_max = (x_max - x_e) / x_d;
	//}
	//else {
	//	tx_min = (x_max - x_e) / x_d;
	//	tx_max = (x_min - x_e) / x_d;
	//}

	//// calculate range for y
	//if (y_d >= 0) {
	//	ty_min = (y_min - y_e) / y_d;
	//	ty_max = (y_max - y_e) / y_d;
	//}
	//else {
	//	ty_min = (y_max - y_e) / y_d;
	//	ty_max = (y_min - y_e) / y_d;
	//}

	//// calculate range for z
	//if (z_d >= 0) {
	//	tz_min = (z_min - z_e) / z_d;
	//	tz_max = (z_max - z_e) / z_d;
	//}
	//else {
	//	tz_min = (z_max - z_e) / z_d;
	//	tz_max = (z_min - z_e) / z_d;
	//}

	//double t_min = std::max({ tx_min, ty_min, tz_min });
	//double t_max = std::min({ tx_max, ty_max, tz_max });

	//// is a hit if t_min < t_max and either min_t or max_t are within the range
	//if (t_min < t_max) {
	//	if ((min_t > t_min && min_t < t_max) || (max_t > t_min && max_t < t_max)) {
	//		return true;
	//	}
	//}

	//return false;
  ////////////////////////////////////////////////////////////////////////////
}
