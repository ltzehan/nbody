#pragma once

#include "float3.h"
#include "particle.h"
#include "region.h"

const float OCTREE_THETA = 0.75;

// node of octree
struct Node {

	Node* children[8];
	bool hasChildren;

	// region covered by this node
	Region region;

	// physical parameters
	int n;			// number of bodies (including those in child nodes)
	float3 sum_pos;	// sum of all child particle positions
	float3 cmass;	// center of mass

	Node(Region region) : region(region), hasChildren(false), n(0) {}

	~Node() {
		for (int i = 0; i < 8; i++) {
			delete children[i];
		}
	}
	
	void split();
	bool add_particle(Particle pt);

};