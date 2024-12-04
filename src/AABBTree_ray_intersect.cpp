#include "AABBTree.h"
#include <iostream>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
	
	//std::cout << "depth: " << depth << " ";
	//if (depth == 6) {
	//	std::cout << "DEPTH 6 SIZE: " << num_leaves << " ";
	//}

	// if ray doesn't hit bbox, return false
	if (!ray_intersect_box(ray, box, min_t, max_t)) {
		//std::cout << " NO HIT ";
		//std::cout << " min_corner " << box.min_corner << " max_corner " << box.max_corner << "\n";
		//std::cout << "ray information: ray origin " << ray.origin << " ray dir " << ray.direction << "\n";
		return false;
	}


	double left_t; double right_t;
	std::shared_ptr<Object> left_descendant;
	std::shared_ptr<Object> right_descendant;
	bool left_hit; bool right_hit;
	
	// if ray hits bbox, recursively call this function on left and right subtrees (DFS)
	//std::cout << "go left \n";
	left_hit = (left != NULL) && (left->ray_intersect(ray, min_t, max_t, left_t, left_descendant));
	//std::cout << "go right \n";
	right_hit = (right != NULL) && (right->ray_intersect(ray, min_t, max_t, right_t, right_descendant));

	// if neither left or right are hit, return false
	if (!(left_hit || right_hit)) {
		return false;
	}

	// if only 2 leaves or less, then set left and right descendant to be left and right pointers
	if (num_leaves <= 2) {
		left_descendant = left;
		right_descendant = right;
	}

	// return minimum t value and update descendant if hit
	if (left_hit && right_hit) {
		if (left_t < right_t) {
			t = left_t;
			descendant = left_descendant;
		}
		else {
			t = right_t;
			descendant = right_descendant;
		}
	}
	else if (left_hit) {
		t = left_t;
		descendant = left_descendant;
	}
	else if (right_hit) {
		t = right_t;
		descendant = right_descendant;
	}

	return true;
  ////////////////////////////////////////////////////////////////////////////
}

