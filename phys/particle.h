#pragma once

#include <vector>
#include "float3.h"
#include "region.h"

// all particles taken to have identical mass of unity
struct Particle {

	// physical parameters
	float3 pos;
	float3 vel;
	float3 acc;

	Particle(float3 pos, float3 vel, float3 acc) : pos(pos), vel(vel), acc(acc) {}

	static Region randomize(std::vector<Particle>& ptlist, int n);

};