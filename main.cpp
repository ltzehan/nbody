// Entry point for simulation
// Creates new simulation from runtime supplied arguments

#include <string>
#include "test.h"
#include "simulation.h"

void print_help() {

	printf("\n");
	printf("-h: Prints this dialog\n");
	printf("-n: Sets number of bodies (positive integer expected)\n");
	printf("-f: Sets number of frames (positive integer expected)\n");
	printf("-t: Set timestep for each frame (positive float expected)\n");
	printf("\n");
	printf("EX: nbody.exe [-h] [-n N] [-f FRAMES] [-t TSTEP]\n");
	printf("\n");

}

// OK:		if arguments are valid
// ERR:		if arguments are missing / out of place / unrecognized
// HELP:	used only when -h is called
enum class ParseFlag { OK, ERR, HELP };

const char* NO_VAL_TEMPLATE = "No value specified for flag %s\n";
const char* EXP_POS_INT_TEMPLATE = "Expected positive integer for flag %s\n";
const char* EXP_POS_FLOAT_TEMPLATE = "Expected positive float for flag %s\n";

// fills configuration with values from runtime arguments
ParseFlag parse_flags(int argc, char* argv[], Config* config) {

	using namespace std;

	// parse runtime arguments
	if (argc == 1) {
		// no arguments
		return ParseFlag::OK;
	}
	else {

		// ignore executable name at argv[0]
		int i = 1;
		while (i < argc) {

			string s = argv[i];
			if (s == "-h") {
				// print help dialog
				return ParseFlag::HELP;
			}
			else if (s == "-n") {
				// set number of bodies

				if (++i >= argc) {
					printf(NO_VAL_TEMPLATE, "-n");
					return ParseFlag::ERR;
				}
				else {
					int x = -1;
					x = stoi(argv[i]);

					if (x > 0) {
						config->n = x;
					}
					else {
						printf(EXP_POS_INT_TEMPLATE, "-n");
						return ParseFlag::ERR;
					}
				}
			}
			else if (s == "-f") {
				// set number of frames

				if (++i >= argc) {
					printf(NO_VAL_TEMPLATE, "-f");
					return ParseFlag::ERR;
				}
				else {
					int x = -1;
					x = stoi(argv[i]);

					if (x > 0) {
						config->frames = x;
					}
					else {
						printf(EXP_POS_INT_TEMPLATE, "-f");
						return ParseFlag::ERR;
					}
				}
			}
			else if (s == "-t") {
				// set timestep

				if (++i >= argc) {
					printf(NO_VAL_TEMPLATE, "-t");
					return ParseFlag::ERR;
				}
				else {
					float x = -1;
					x = stof(argv[i]);

					if (x > 0) {
						config->tstep = x;
					}
					else {
						printf(EXP_POS_FLOAT_TEMPLATE, "-t");
						return ParseFlag::ERR;
					}
				}
			}
			else {
				printf("Invalid or out of place arguments\n");
				return ParseFlag::ERR;
			}

			i++;
		}

	}

	return ParseFlag::OK;
}

int main(int argc, char* argv[]) {

	TEST_NBODY(false);

	Config config;
	// update simulation configuration from runtime arguments
	auto ret_flag = parse_flags(argc, argv, &config);

	if (ret_flag == ParseFlag::ERR) {
		printf("Run with flag -h for help\n");
		return -1;
	}
	else if (ret_flag == ParseFlag::HELP) {
		print_help();
		return 0;
	}
	else if (ret_flag == ParseFlag::OK) {

		Simulation sim(config);
		sim.start();

	}

	return 0;
}