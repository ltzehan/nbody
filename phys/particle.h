#pragma once

#include <vector>
#include "float3.h"
#include "region.h"

// all particles taken to have identical mass of unity
struct Particle {

	// doubt anyone in their right mind will run an nbody that overflows this
	int id;

	// physical parameters
	float3 pos;
	float3 vel;
	float3 acc;

	Particle(int id, float3 pos, float3 vel, float3 acc) : id(id), pos(pos), vel(vel), acc(acc) {}

	void update();

	static BoundingBox randomize(std::vector<Particle>& ptlist, int n);

};