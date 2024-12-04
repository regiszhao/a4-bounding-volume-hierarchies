#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <iostream>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////

	int N = objects.size();

	// put all objects in list into bounding box
	for (int i = 0; i < N; i++) {
		insert_box_into_box(objects[i]->box, box);
	}

	// if only one object, assign to left node, assign null to right node
	if (N == 1) {
		left = objects[0];
		right = NULL;
	}
	// if two objects, assign to left and right
	else if (N == 2) {
		left = objects[0];
		right = objects[1];
	}
	// if more than two objects
	else {
		// find midpoint along longest axis
		Eigen::RowVector3d axis_lengths = box.max_corner - box.min_corner;
		double max_axis_length = 0.0;
		double cur_axis_length;
		int axis;
		for (int i = 0; i < 3; i++) {
			cur_axis_length = abs(axis_lengths(i));
			if ( cur_axis_length > max_axis_length) {
				max_axis_length = cur_axis_length;
				axis = i;
			}
		}
		double midpt = box.center()(axis);

		// initialize left and right object list
		std::vector<std::shared_ptr<Object> > left_objects;
		std::vector<std::shared_ptr<Object> > right_objects;
		// iterate through all objects, if their midpoint is less than bounding box midpoint, put into left, otherwise put into right
		for (int i = 0; i < N; i++) {
			if (objects[i]->box.center()(axis) < midpt) {
				left_objects.push_back(objects[i]);
				//if (i == 991) {
				//	std::cout << "going left\n";
				//}
			}
			else {
				right_objects.push_back(objects[i]);
				//if (i == 991) {
				//	std::cout << "going right\n";
				//}
			}
		}

		// if one of the lists has no objects, pull an object from the other list to keep tree balanced
		if (left_objects.size() == 0) {
			left_objects.push_back(right_objects.back());
			right_objects.pop_back();
		}
		else if (right_objects.size() == 0) {
			right_objects.push_back(left_objects.back());
			left_objects.pop_back();
		}

		// recursively create AABBTree for left and right subtrees
		left = std::make_shared<AABBTree>(left_objects, depth + 1);
		right = std::make_shared<AABBTree>(right_objects, depth + 1);
	}

  ////////////////////////////////////////////////////////////////////////////
}
