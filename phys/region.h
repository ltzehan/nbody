#pragma once

#include <algorithm>
#include <string>
#include "float3.h"

// I'm pretty sure this is already orders of magnitude too big
const float INF = 10E10f;

struct Region {

	// position of the region's center
	float3 center;
	// side lengths of region
	float3 dim;

	Region() {}
	Region(float3 center, float3 dim) : center(center), dim(dim) {}

	// returns geometric mean of Region dimensions
	// I think this makes sense for a cuboid Region
	float get_gm() {
		return pow(dim.x * dim.y * dim.z, 0.333333);
	}

	// returns a Region corresponding to the child node
	Region get_subregion(const int child_id) {

		// find new center of region
		float3 dr = dim / 4;
		float dx = dr.x * (child_id & 0x001 ? -1 : 1);
		float dy = dr.y * (child_id & 0x010 ? -1 : 1);
		float dz = dr.z * (child_id & 0x100 ? -1 : 1);

		float3 child_center = center - float3(dx, dy, dz);
		float3 child_dim = dim / 2;

		return Region(child_center, child_dim);
	}

};

// different representation of Region with methods relevant only to
// the axis aligned bounding box computation
struct BoundingBox {

	float3 min_corner;
	float3 max_corner;

	BoundingBox() : min_corner(float3(INF, INF, INF)), max_corner(float3(-INF, -INF, -INF)) {}
	BoundingBox(float3 min, float3 max) : min_corner(min), max_corner(max) {}

	// updates BoundingBox to enclose exterior positions
	void update(const float3 pos) {
		min_corner.x = std::min(min_corner.x, pos.x);
		min_corner.y = std::min(min_corner.y, pos.y);
		min_corner.z = std::min(min_corner.z, pos.z);

		max_corner.x = std::max(max_corner.x, pos.x);
		max_corner.y = std::max(max_corner.y, pos.y);
		max_corner.z = std::max(max_corner.z, pos.z);
	}

	// converts BoundingBox to Region representation
	Region to_region() {
		float3 center = (min_corner + max_corner) / 2;
		float3 dim = (max_corner - min_corner);

		return Region(center, dim);
	}

	// string override
	std::string to_string() {
		return "min_corner = " + min_corner.to_string() + "\nmax_corner = " + max_corner.to_string();
	}

};