#define _USE_MATH_DEFINES
#include <cmath>

// for portability's sake
#ifndef _MATH_DEFINES_DEFINED
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#endif

#include <random>
#include "particle.h"

// I'm pretty sure this is already orders of magnitude too big
#define INF 10E10

// initialize particle list and randomize properties
Region Particle::randomize(std::vector<Particle>& ptlist, int n) {

	using dstr = std::uniform_real_distribution<float>;

	dstr azimuth(0, 2 * M_PI);
	dstr elevation(-1, 1);
	dstr mass_ratio(0, 1);

	dstr velq(0, 1);
	dstr velg(0, 0.1);

	// initialize random number generator
	std::random_device rd;
	std::mt19937 rng(rd());

	// find initial axis aligned bounding box for particles
	Region bounding_box(
		float3(INF, INF, INF),
		float3(-INF, -INF, -INF)
	);

	// using Plummer model for particles
	for (int i = 0; i < n; i++) {

		// radial distance
		float r = 0.5 / sqrt(pow(mass_ratio(rng), -0.666666) - 1);
		// spherical coordinates
		float azi = azimuth(rng);
		float elv = acos(elevation(rng)) - M_PI_2;

		float3 pos(
			r * cos(elv) * cos(azi),
			r * cos(elv) * sin(azi),
			r * sin(elv)
		);

		// update bounding box
		auto minc = bounding_box.min_corner;
		auto maxc = bounding_box.max_corner;

		minc.x = std::min(minc.x, pos.x);
		minc.y = std::min(minc.y, pos.y);
		minc.z = std::min(minc.z, pos.z);

		maxc.x = std::max(maxc.x, pos.x);
		maxc.y = std::max(maxc.y, pos.y);
		maxc.z = std::max(maxc.z, pos.z);

		// rejection sampling for velocities
		float q;
		float g;
		do {

			q = velq(rng);
			g = velg(rng);

		} while (g > pow((q*q)*(1 - (q*q)), 3.5));

		// velocity magntitude
		float v = q * M_SQRT2 * pow(1.0 + r * r, -0.25);
		// spherical coordinates
		azi = azimuth(rng);
		elv = acos(elevation(rng)) - M_PI_2;

		float3 vel(
			v * cos(elv) * cos(azi),
			v * cos(elv) * sin(azi),
			v * sin(elv)
		);

		float3 acc;

		ptlist.emplace_back(pos, vel, acc);
	}

	return bounding_box;
}
