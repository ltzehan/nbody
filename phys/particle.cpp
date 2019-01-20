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

// initialize particle list and randomize properties
BoundingBox Particle::randomize(std::vector<Particle>& ptlist, int n) {

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
	BoundingBox bb;

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
		bb.update(pos);

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

		ptlist.emplace_back(i, pos, vel, acc);
	}

	return bb;
}
