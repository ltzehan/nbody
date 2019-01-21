#pragma once

#include "float3.h"
#include "region.h"

#define RUN_TEST_NBODY
#define TEST_FLOAT3 1
#define TEST_REGION 1

// this is the pinnacle of unit testing
#ifdef RUN_TEST_NBODY
#define TEST_NBODY() nbody_test()
#else
#define TEST_NBODY()
#endif

#define TEST_EQ(x, y) { assert_eq((x), (y), __LINE__); }
inline void assert_eq(float3 x, float3 y, int line) {
	if (x != y) {
		fprintf(stderr, ">> Test failed at line %d: compared %s to %s\n", line, x.to_string().c_str(), y.to_string().c_str());
		getchar();
		exit(-1);
	}
}
inline void assert_eq(float x, float y, int line) {
	if (abs(x - y) > FLOAT_EPS) {
		fprintf(stderr, ">> Test failed at line %d: compared %f to %f\n", line, x, y);
		getchar();
		exit(-1);
	}
}

namespace {

	bool test_float3() {

		float3 zero;
		TEST_EQ(zero, float3(0, 0, 0));

		float3 f1(0.1, 5, -250.5);
		float3 f2(-4.23, 0.05, 7);

		float3 add(-4.13, 5.05, -243.5);
		float3 sub(4.33, 4.95, -257.5);

		TEST_EQ(f1 + f2, add);
		TEST_EQ(f1 - f2, sub);

		f1 += f2;
		TEST_EQ(f1, add);

		float3 mul(-5.076, 0.06, 8.4);
		float3 div(-2.115, 0.025, 3.5);

		TEST_EQ(f2 * 1.2, mul);
		TEST_EQ(f2 / 2, div);

		float3 r(0.25, 0.5, 0.5);
		float dist = calc_dist(r);
		TEST_EQ(dist, 0.75);

		return true;
	}

	bool test_region() {

		float3 parent_center(0, 1.5, 5);
		float3 parent_dim(5, 25, 8);

		Region reg(parent_center, parent_dim);

		TEST_EQ(reg.get_gm(), 10.0);

		Region child_0 = reg.get_subregion(0);
		Region child_6 = reg.get_subregion(6);

		TEST_EQ(child_0.center, float3(-1.25, -4.75, 3));
		TEST_EQ(child_6.center, float3(-1.25, 7.75, 7));
		TEST_EQ(child_0.dim, float3(2.5, 12.5, 4));
		TEST_EQ(child_6.dim, float3(2.5, 12.5, 4));

		BoundingBox bb;
		float3 f1(-1.5, 3.7, -10);
		float3 f2(-7.2, 1, 8.9);

		bb.update(f1);
		bb.update(f2);

		TEST_EQ(bb.max_corner, float3(-1.5, 3.7, 8.9));
		TEST_EQ(bb.min_corner, float3(-7.2, 1, -10));

		Region bb_reg = bb.to_region();

		TEST_EQ(bb_reg.center, float3(-4.35, 2.35, -0.55));
		TEST_EQ(bb_reg.dim, float3(5.7, 2.7, 18.9));

		return true;
	}

}

inline void nbody_test() {

	printf(">> Running tests\n");

	if (TEST_FLOAT3 && test_float3()) printf(">> float3 test OK\n");
	if (TEST_REGION && test_region()) printf(">> Region test OK\n");

	printf(">> All tests done\n");

	getchar();
	exit(0);
}