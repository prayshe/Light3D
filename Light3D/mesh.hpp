#pragma once

#include <vector>
#include "math.hpp"

class Mesh {
public:
	Mesh() {
		position = { 0.0, 0.0, 0.0 };
		rotation = { 0.0, 0.0, 0.0 };
		scaling = { 1.0, 1.0, 1.0 };
		translation = { 0.0, 0.0, 0.0 };
	}
	void addVertex(float x, float y, float z) {
		vertices.push_back(VECTOR3{ x, y, z });
	}
	void addFace(int a, int b, int c) {
		faces.push_back(a);
		faces.push_back(b);
		faces.push_back(c);
	}
	VECTOR3 position;
	VECTOR3 rotation;
	VECTOR3 scaling;
	VECTOR3 translation;
public:
	std::vector<VECTOR3> vertices;
	std::vector<int> faces;
};