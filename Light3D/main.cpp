#include "engine.hpp"

void Init()
{
	Engine* engine = Engine::CreateSingleEngine();
	Mesh mesh;
	mesh.addVertex(-1, 1, 1);
	mesh.addVertex(1, 1, 1);
	mesh.addVertex(-1, -1, 1);
	mesh.addVertex(1, -1, 1);
	mesh.addVertex(-1, 1, -1);
	mesh.addVertex(1, 1, -1);
	mesh.addVertex(1, -1, -1);
	mesh.addVertex(-1, -1, -1);
	mesh.addFace(0, 1, 2);
	mesh.addFace(1, 2, 3);
	mesh.addFace(1, 3, 6);
	mesh.addFace(1, 5, 6);
	mesh.addFace(0, 1, 4);
	mesh.addFace(1, 4, 5);
	mesh.addFace(2, 3, 7);
	mesh.addFace(3, 6, 7);
	mesh.addFace(0, 2, 7);
	mesh.addFace(0, 4, 7);
	mesh.addFace(4, 5, 6);
	mesh.addFace(4, 6, 7);
	engine->addMesh(mesh);
	engine->setMode(RENDER_WIREFRAME);
}

void Draw()
{
	Engine* engine = Engine::CreateSingleEngine();
	Mesh &mesh = engine->getMesh(0);
	mesh.rotation.x += 0.01;
	mesh.rotation.y += 0.01;
	HDC hDC = GetDC(g_hMainWindow);
	BitBlt(hDC, 0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, 0, 0, 0, BLACKNESS);
	engine->Render(hDC);
	ReleaseDC(g_hMainWindow, hDC);
}

void Exit()
{

}
