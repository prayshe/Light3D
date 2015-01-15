#pragma once

#ifndef WIN32_LEAN_ANDMEAN
	#define WIN32_LEAN_AND_MEAN
#endif


#include <windows.h>
#include <windowsx.h>
#include <cstdio>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <cmath>


#define MAIN_WINDOW_CLASS_NAME			_T("Soft3DEngineClass")
#define MAIN_WINDOW_TITLE				_T("D3Engine")
#define MAIN_WINDOW_WIDTH				640
#define MAIN_WINDOW_HEIGHT				480


extern HINSTANCE g_hInstance;
extern HWND g_hMainWindow;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern void Main();
extern void Init();
extern void Draw();
extern void Exit();