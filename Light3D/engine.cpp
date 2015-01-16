#include "engine.hpp"

Engine* Engine::instance = NULL;

void Engine::Render(HDC hDC)
{
	static int cw = MAIN_WINDOW_WIDTH >> 1;
	static int ch = MAIN_WINDOW_HEIGHT >> 1;

	MATRIX44 view = LookAt({ 0.0, 0.0, -10.0 }, { 0.0, 0, 0.0 }, { 0.0, 1.0, 0.0 });
	MATRIX44 proj = Perspective(0.78, (float)MAIN_WINDOW_WIDTH / (float)MAIN_WINDOW_HEIGHT, 0.01, 1.0);

	int n = meshes.size();
	if (mode == RENDER_MODE::RENDER_POINT) {
		for (int i = 0; i < n; ++i) {
			Mesh &mesh = meshes[i];
			MATRIX44 world = Multiply(Multiply(Rotation(mesh.rotation), Scaling(mesh.scaling)), Translation(mesh.translation));
			MATRIX44 transformation = Multiply(Multiply(world, view), proj);
			int m = mesh.vertices.size();
			for (int j = 0; j < m; ++j) {
				VECTOR3 projected = HomogeneousTransform(mesh.vertices[j], transformation);
				int x = projected.x * MAIN_WINDOW_WIDTH + cw;
				int y = -projected.y * MAIN_WINDOW_HEIGHT + ch;
				SetPixel(hDC, x, y, RGB(255, 255, 255));
				char s[10];
				sprintf(s, "%d", j);
				TextOutA(hDC, x, y, s, 1);
			}
		}
	}
	else if (mode == RENDER_MODE::RENDER_WIREFRAME) {
		static HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hDC, pen);
		for (int i = 0; i < n; ++i) {
			
			Mesh &mesh = meshes[i];
			MATRIX44 world = Multiply(Multiply(Rotation(mesh.rotation), Scaling(mesh.scaling)), Translation(mesh.translation));
			MATRIX44 transformation = Multiply(Multiply(world, view), proj);
			int m = mesh.faces.size() / 3;
			for (int j = 0, k = 0; j < m; ++j) {
				int t1 = mesh.faces[k++];
				int t2 = mesh.faces[k++];
				int t3 = mesh.faces[k++];
				VECTOR3 a = HomogeneousTransform(mesh.vertices[t1], transformation);
				VECTOR3 b = HomogeneousTransform(mesh.vertices[t2], transformation);
				VECTOR3 c = HomogeneousTransform(mesh.vertices[t3], transformation);
				int x1 = a.x * MAIN_WINDOW_WIDTH + cw;
				int y1 = -a.y * MAIN_WINDOW_HEIGHT + ch;
				int x2 = b.x * MAIN_WINDOW_WIDTH + cw;
				int y2 = -b.y * MAIN_WINDOW_HEIGHT + ch;
				int x3 = c.x * MAIN_WINDOW_WIDTH + cw;
				int y3 = -c.y * MAIN_WINDOW_HEIGHT + ch;
				MoveToEx(hDC, x1, y1, 0);
				LineTo(hDC, x2, y2);
				LineTo(hDC, x3, y3);
				LineTo(hDC, x1, y1);
			}
		}
	}
}