#pragma once

// determine filesystem to use from feature test macros
#ifdef __cpp_lib_experimental_filesystem
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#elif __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#else
#error "no filesystem support found"
#endif

#include <vector>
#include "particle.h"

struct VTKWriter {

	VTKWriter(const int n);

	void write(std::vector<Particle>& ptlist);

private:

	fs::path outdir;
	int frame;
	int n;

};