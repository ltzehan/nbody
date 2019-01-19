#pragma once

#include "float3.h"

struct Region {

	// corners are always defined such that min_corner < max_corner
	// faster computation of contains() using this representation
	float3 min_corner;
	float3 max_corner;

	Region() {}
	Region(float3 min, float3 max) : min_corner(min), max_corner(max) {}

	// determines if the region encloses the coordinates given
	bool contains(float3 pos) {
		return (pos > min_corner) && (pos < max_corner);
	}

	// returns a new Region with shifted coordinates
	Region translate(float dx, float dy, float dz) {

		float3 dr(dx, dy, dz);

		float3 f1 = min_corner + dr;
		float3 f2 = max_corner + dr;

		return Region(f1, f2);
	}
};
