#pragma once

#include <vector>
#include "particle.h"
#include "octree.h"
#include "vtkwriter.h"

struct Config {
	// default simulation configuration
	int frames = 25;
	int n = 2048;
	float tstep = 0.2;	// we can worry about physical scales later
};

struct Simulation {

	Simulation(const Config config) {
		frames = config.frames;
		n = config.n;
		tstep = config.tstep;
	}

	void start();

private:

	// number of frames to be rendered
	int frames;
	// number of bodies
	int n;
	// timestep per frame
	float tstep;

	std::vector<Particle> ptlist;

	void update();
	void out(VTKWriter& vtkw);

	// for computation purposes 
	BoundingBox bounding_box;
	Node* tree;

};