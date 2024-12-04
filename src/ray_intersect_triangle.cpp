#include "ray_intersect_triangle.h"
#include <Eigen/Dense>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////

	// compute reused variables in matrices
	double x_a = A(0); double y_a = A(1); double z_a = A(2);
	double x_b = B(0); double y_b = B(1); double z_b = B(2);
	double x_c = C(0); double y_c = C(1); double z_c = C(2);
	double x_d = ray.direction(0); double y_d = ray.direction(1); double z_d = ray.direction(2);
	double x_e = ray.origin(0); double y_e = ray.origin(1); double z_e = ray.origin(2);

	double x_ab = x_a - x_b; double y_ab = y_a - y_b; double z_ab = z_a - z_b;
	double x_ac = x_a - x_c; double y_ac = y_a - y_c; double z_ac = z_a - z_c;
	double x_ae = x_a - x_e; double y_ae = y_a - y_e; double z_ae = z_a - z_e;

	// compute determinant of A matrix
	Eigen::Matrix3d A_matrix;
	A_matrix << x_ab, x_ac, x_d,
		y_ab, y_ac, y_d,
		z_ab, z_ac, z_d;
	double det_A = A_matrix.determinant();

	// if det_A is zero, not solvable
	if (det_A == 0) { // TOLERANCE?
		return false;
	}

	// compute t
	Eigen::Matrix3d t_cramer;
	t_cramer << x_ab, x_ac, x_ae,
		y_ab, y_ac, y_ae,
		z_ab, z_ac, z_ae;
	double det_t_cramer = t_cramer.determinant();
	t = det_t_cramer / det_A;
	// if t out of range, return false
	if (t < min_t || t > max_t) {
		return false;
	}

	// compute gamma
	Eigen::Matrix3d g_cramer;
	g_cramer << x_ab, x_ae, x_d,
		y_ab, y_ae, y_d,
		z_ab, z_ae, z_d;
	double det_g_cramer = g_cramer.determinant();
	double gamma = det_g_cramer / det_A;
	// if gamma out of range of [0,1], return false
	if (gamma < 0 || gamma > 1) {
		return false;
	}

	// compute beta
	Eigen::Matrix3d b_cramer;
	b_cramer << x_ae, x_ac, x_d,
		y_ae, y_ac, y_d,
		z_ae, z_ac, z_d;
	double det_b_cramer = b_cramer.determinant();
	double beta = det_b_cramer / det_A;
	// if beta out of range of [0,1-gamma], return false
	if ((beta < 0) || (beta > 1 - gamma)) {
		return false;
	}

	return true;
  ////////////////////////////////////////////////////////////////////////////
}

