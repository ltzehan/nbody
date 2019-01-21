#pragma once

#include "float3.h"
#include "particle.h"
#include "region.h"

// node of octree
struct Node {

	Node* children[8] = { NULL };
	
	bool is_leaf;
	// leaf_id is equivalent to the particle id stored at the leaf node
	int leaf_id;

	// region covered by this node
	Region region;

	// physical parameters
	int n;			// number of bodies (including those in child nodes)
	float3 sum_pos;	// sum of all child particle positions
	float3 cmass;	// center of mass

	Node(Region region) : is_leaf(true), region(region), n(0), sum_pos(float3(0, 0, 0)) {}

	~Node() {
		for (int i = 0; i < 8; i++) {
			if (children[i]) {
				delete children[i];
			}
		}
	}
	
	int find_index(float3 pos);
	void add_particle(const Particle& pt);

	void calc_force(Particle& pt);

};