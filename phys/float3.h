// Represents a vector in 3 dimensions
// It's like CUDA's float3 but with more freedom because we don't care about coalesced access and complicated stuff like that

#pragma once

#include <string>

struct float3 {

	float x, y, z;

	float3() : x(0), y(0), z(0) {}
	float3(float x, float y, float z) : x(x), y(y), z(z) {}

	// override for use with VTKWriter
	friend std::ostream& operator<< (std::ostream& stream, const float3& f) {
		stream << f.x << " " << f.y << " " << f.z << "\n";
		return stream;
	}

	// string representation
	std::string to_string() {
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	// arithmetic operator overloads
	friend bool operator< (const float3& f1, const float3& f2) {
		return (f1.x < f2.x) && (f1.y < f2.y) && (f1.z < f2.z);
	}

	friend bool operator> (const float3& f1, const float3& f2) {
		return (f1.x > f2.x) && (f1.y > f2.y) && (f1.z > f2.z);
	}

	friend float3 operator+ (const float3& f1, const float3& f2) {
		return float3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
	}

	friend void operator+= (float3& f1, const float3& f2) {
		f1.x += f2.x;
		f1.y += f2.y;
		f1.z += f2.z;
	}

	friend float3 operator- (const float3& f1, const float3& f2) {
		return float3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
	}

	// multiplication or division by a scalar over all elements
	template <typename T>
	friend float3 operator* (const float3& f, const T& k) {
		return float3(f.x * k, f.y * k, f.z * k);
	}

	template <typename T>
	friend float3 operator/ (const float3& f, const T& k) {
		return float3(f.x / k, f.y / k, f.z / k);
	}

};

// calculates the Euclidean distance between two points
inline float calc_dist(const float3 dr) {
	return sqrt(dr.x*dr.x + dr.y*dr.y + dr.z*dr.z);
}
inline float calc_dist(const float3 f1, const float3 f2) {
	return calc_dist(f1 - f2);
}