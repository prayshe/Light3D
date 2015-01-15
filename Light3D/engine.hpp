#pragma once

#include <Windows.h>
#include <vector>
#include "window.hpp"
#include "mesh.hpp"

enum RENDER_MODE {
	RENDER_POINT,
	RENDER_WIREFRAME,
	RENDER_FACE
};

class Engine {
public:
	static Engine* CreateSingleEngine() {
		if (instance == NULL) {
			instance = new Engine();
		}

		return instance;
	}
	~Engine() {
		if (instance) {
			delete instance;
			instance = NULL;
		}
	}
	void addMesh(const Mesh &mesh) {
		meshes.push_back(mesh);
	}
	Mesh& getMesh(int id) {
		return meshes[id];
	}
	void setMode(RENDER_MODE mode) {
		this->mode = mode;
	}
	void Render(HDC);
private:
	Engine()
	{}
	static Engine *instance;
	std::vector<Mesh> meshes;
	RENDER_MODE mode;
};