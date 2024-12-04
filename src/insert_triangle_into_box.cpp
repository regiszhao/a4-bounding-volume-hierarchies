#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////

	Eigen::RowVector3d B_min_corner = B.min_corner;
	Eigen::RowVector3d B_max_corner = B.max_corner;

	// update min_corner
	B.min_corner(0) = std::min({ a(0), b(0), c(0), B_min_corner(0) });
	B.min_corner(1) = std::min({ a(1), b(1), c(1), B_min_corner(1) });
	B.min_corner(2) = std::min({ a(2), b(2), c(2), B_min_corner(2) });

	// update max_corner
	B.max_corner(0) = std::max({ a(0), b(0), c(0), B_max_corner(0) });
	B.max_corner(1) = std::max({ a(1), b(1), c(1), B_max_corner(1) });
	B.max_corner(2) = std::max({ a(2), b(2), c(2), B_max_corner(2) });

  ////////////////////////////////////////////////////////////////////////////
}


