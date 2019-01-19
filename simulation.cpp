// Responsible for actual control flow of the program

#include <chrono>
#include "simulation.h"

using Clock = std::chrono::high_resolution_clock;

void Simulation::start() {

	// calculates elapsed time in seconds
	auto get_elapsed = [](auto start, auto end) {
		std::chrono::milliseconds dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		long long int ms = dur.count();
		return static_cast<float>(ms) / 1000;
	};

	// start time for simulation initialization
	auto start_time = Clock::now();

	// create output handler
	VTKWriter vtkw(n);

	// initialize particles and get initial bounding box of system
	bounding_box = Particle::randomize(ptlist, n);
	out(vtkw);

	// end time for simulation initialization
	auto end_time = Clock::now();
	auto elapsed_time = get_elapsed(start_time, end_time);

	printf("Finished initialization in %.4fs\n", elapsed_time);

	printf("Simulation started for %d frames with %d bodies\n", frames, n);
	
	// start time for simulation
	start_time = Clock::now();

	for (int i = 0; i < frames; i++) {
		update();
		out(vtkw);
	}

	// end time for simulation
	end_time = Clock::now();
	elapsed_time = get_elapsed(start_time, end_time);

	printf("Simulation ended (%d frames in %.4fs; FPS = %.2f)\n", frames, elapsed_time, (elapsed_time / frames));
	getchar();
}

// writes updated particle positions to file
// might be accompanied by visualization in the (far) future
void Simulation::out(VTKWriter& vtkw) {
	vtkw.write(ptlist);
}

// update particles by one timestep
void Simulation::update() {

	// build tree
	tree = new Node(bounding_box);

	for (auto& pt : ptlist) {
		tree->add_particle(pt);
	}

}



