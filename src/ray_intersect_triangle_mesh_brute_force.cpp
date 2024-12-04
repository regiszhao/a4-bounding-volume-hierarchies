#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////

	// set hit_t to initially be infinity
	hit_t = std::numeric_limits<double>::infinity();
	double cur_t;
	bool hit = false;

	// loop through F
	for (int row = 0; row < F.rows(); row++) {

		// get corners of triangle
		int A_index = F(row, 0);
		int B_index = F(row, 1);
		int C_index = F(row, 2);
		Eigen::RowVector3d A = V.row(A_index);
		Eigen::RowVector3d B = V.row(B_index);
		Eigen::RowVector3d C = V.row(C_index);

		// if ray hits triangle, update hit_t and hit_f (if t is a new min)
		if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, cur_t)) {
			if (cur_t < hit_t) {
				hit_t = cur_t;
				hit_f = row;
				hit = true;
			}
		}
	}

	return hit;
  ////////////////////////////////////////////////////////////////////////////
}
