#include "window.hpp"
#include "engine.hpp"

HINSTANCE g_hInstance = NULL;
HWND g_hMainWindow = NULL;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int iReturnValue = 0;

	WNDCLASSEX wce;
	memset(&wce, 0, sizeof(WNDCLASSEX));
	wce.cbSize = sizeof(WNDCLASSEX);
	wce.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wce.lpfnWndProc = (WNDPROC)MainWindowProc;
	wce.hInstance = hInstance;
	wce.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wce.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce.lpszClassName = MAIN_WINDOW_CLASS_NAME;


	srand((unsigned)time(NULL));

	if (RegisterClassEx(&wce) != 0) {
		g_hInstance = hInstance;

		RECT window = { 0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT };
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		AdjustWindowRectEx(&window, dwStyle, FALSE, dwExStyle);

		int window_width = window.right - window.left;
		int window_height = window.bottom - window.top;

		int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
		int x = (iScreenWidth - window_width) >> 1;
		int y = (iScreenHeight - window_height) >> 1;

		g_hMainWindow = CreateWindowEx(dwExStyle, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE,
			dwStyle, x, y, window_width, window_height, NULL, NULL, g_hInstance, NULL);

		if (g_hMainWindow != NULL) {
			Main();
		} else {
			MessageBox(NULL, _T("The main window can not be created!"), _T("Error..."), MB_OK | MB_ICONERROR);
			iReturnValue = -1;
		}

		UnregisterClass(MAIN_WINDOW_CLASS_NAME, hInstance);
	} else {
		MessageBox(NULL, _T("The main window class can not be registered!"), _T("Error..."), MB_OK | MB_ICONERROR);
		iReturnValue = -1;
	}

	return iReturnValue;
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int lResult = 0;

	switch (uMsg) {
		case WM_PAINT:
		{}
		break;
		case WM_DESTROY: {
			PostQuitMessage(0);
		} break;
		case WM_KEYDOWN: {
			if (wParam == VK_ESCAPE) {
				DestroyWindow(hWnd);
			}
		} break;
		default: {
			lResult = DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	return lResult;
}


void Main()
{
	//if (AllocConsole()) {
	//	freopen("CONOUT$", "w", stdout);
	//}

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	Init();

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Draw();
		Sleep(1);
	}

	Exit();
}