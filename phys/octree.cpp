#include "octree.h"

// splits the current region into 8 subregions
void Node::split() {

	hasChildren = true;

	// half the side length of parent region
	float3 dim = (region.max_corner - region.min_corner) / 2;
	float3 center = (region.min_corner + region.max_corner) / 2;

	// use region at children[0] as reference region
	Region r(region.min_corner, center);

	// assignment of nodes follows a Z-order curve
	children[0] = new Node(r);
	children[1] = new Node(r.translate(dim.x, 0, 0));
	children[2] = new Node(r.translate(0, dim.y, 0));
	children[3] = new Node(r.translate(dim.x, dim.y, 0));
	children[4] = new Node(r.translate(0, 0, dim.z));
	children[5] = new Node(r.translate(dim.x, 0, dim.z));
	children[6] = new Node(r.translate(0, dim.y, dim.z));
	children[7] = new Node(r.translate(dim.x, dim.y, dim.z));

}

// returns false if particle does not belong in node
// otherwise returns true if particle is added to tree
bool Node::add_particle(Particle pt) {

	if (!region.contains(pt.pos)) {
		// particle is not in node
		return false;
	}

	// otherwise if there are no particles, just directly add to this node
	if (n >= 1) {

		if (!hasChildren) {
			// too many particles in region
			split();
		}

		for (int i = 0; i < 8; i++) {
			// recursively add particle
			bool added = children[i]->add_particle(pt);
			if (added) break;
		}
	}

	// update center of mass of node
	n++;
	sum_pos += pt.pos;
	cmass = sum_pos / n;

	return true;
}