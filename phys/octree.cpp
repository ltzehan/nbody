#include "octree.h"

const float OCTREE_THETA = 0;
const float PHYS_G = 50;

// returns index of child node that encloses this position
int Node::find_index(float3 pos) {
	int id = 0;
	// bitmasking to find index based on Z-order curve
	if (pos.x > region.center.x)
		id |= 0b001;
	if (pos.y > region.center.y)
		id |= 0b010;
	if (pos.z > region.center.z)
		id |= 0b100;

	return id;
}

// recursively adds particle to tree
void Node::add_particle(const Particle& pt) {

	if (n == 0) {
		leaf_id = pt.id;
	}
	
	if (n >= 1) {

		int id = find_index(pt.pos);

		// create new child
		if (!children[id]) {
			children[id] = new Node(region.get_subregion(id));
			is_leaf = false;
		}
		
		children[id]->add_particle(pt);
	}

	// update center of mass of node
	n++;
	sum_pos += pt.pos;
	cmass = sum_pos / n;

}

// computes force between appropriate Node-Particle pairs and updates particle accelerations
void Node::calc_force(Particle& pt) {

	float s = calc_dist(region.center, pt.pos);
	// Barnes-Hut threshold
	float theta = region.get_gm() / s;
	
	// only evaluate force pair if either
	// (1): Node is a leaf that represents another particle, or
	// (2): Node is internal and falls below threshold
	if ((is_leaf && leaf_id != pt.id) || (!is_leaf && theta <= OCTREE_THETA)) {
		// heads up, this assumes particle masses of unity
		
		float3 r = cmass - pt.pos;			// note direction of gravity
		float dist = calc_dist(r);
		float dist3 = dist * dist * dist;	// much faster than using pow()
		
		pt.acc += r * (PHYS_G * n / dist3);

	}
	else if (!is_leaf) {

		// above threshold; go down to child nodes
		for (int i = 0; i < 8; i++) {
			if (children[i]) {
				// child node exists
				children[i]->calc_force(pt);
			}
		}

	}
		
} 