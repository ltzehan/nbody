// Handles filesystem and VTK output files
// Uses no platform dependent functions so should be portable

#include <fstream>
#include "vtkwriter.h"
#include "particle.h"

const std::string DIR_NAME = "outdir";

VTKWriter::VTKWriter(const int n) : n(n) {
	
	// current frame to write as
	frame = 0;

	// try default output directory
	fs::path p = fs::current_path();
	p /= DIR_NAME;

	// check if path already exists
	int uniq_dir = 1;
	while (fs::exists(p)) {
		p.replace_filename(DIR_NAME + "-" + std::to_string(uniq_dir));
		uniq_dir++;
	}

	fs::create_directory(p);
	outdir = p;

}

void VTKWriter::write(std::vector<Particle>& ptlist) {

	fs::path file = outdir / (std::to_string(frame) + ".vtk");

	std::ofstream outf(file);
	// VTK file header
	outf << "# vtk DataFile Version 3.0\n";
	outf << "Particle Data (Frame " << frame << ")\n";
	outf << "ASCII\n";
	outf << "DATASET POLYDATA\n";
	outf << "POINTS " << n << " float\n";

	// write particle positions
	for (int i = 0; i < n; i++) {
		outf << ptlist[i].pos;
	}

	outf.close();

	frame++;
}