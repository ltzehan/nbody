// Represents a vector in 3 dimensions
// It's like CUDA's float3 but with more freedom because we don't care about coalesced access and complicated stuff like that

#pragma once

#include <string>

struct float3 {

	float x, y, z;

	float3() { float3(0, 0, 0); }
	float3(float x, float y, float z) : x(x), y(y), z(z) {}

	// override for use with VTKWriter
	friend std::ostream& operator<< (std::ostream& stream, const float3& f) {
		stream << f.x << " " << f.y << " " << f.z << "\n";
		return stream;
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

	template <typename T>
	friend float3 operator* (const float3& f, const T& k) {
		return float3(f.x * k, f.y * k, f.z * k);
	}

	template <typename T>
	friend float3 operator/ (const float3& f, const T& k) {
		return float3(f.x / k, f.y / k, f.z / k);
	}

};