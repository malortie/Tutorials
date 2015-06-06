// ProgressBar.cpp

// Header required to help detect window version
#include <sdkddkver.h>

// Macro used to reduce namespace pollution
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Reference for various Win32 API functions and 
// structure declarations.
#include <Windows.h>

// Header needed for unicode adjustment support
#include <tchar.h>

#include <CommCtrl.h>

#pragma comment(lib, "comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define ID_DEFAULTPROGRESSCTRL	401
#define ID_SMOOTHPROGRESSCTRL	402
#define ID_VERTICALPROGRESSCTRL	403

//
//
// WndProc - Window procedure
//
//
LRESULT
CALLBACK
WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

//
//
// WinMain - Win32 application entry point.
//
//
int
APIENTRY
wWinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPWSTR lpCmdLine,
int nShowCmd)
{
	INITCOMMONCONTROLSEX iccex;
	iccex.dwSize = sizeof(iccex);
	iccex.dwICC = ICC_PROGRESS_CLASS;

	if (!InitCommonControlsEx(&iccex))
		return 1;

	// Setup window class attributes.
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpszClassName = TEXT("PROGRESSBARSAMPLE");
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;

	// Register window and ensure registration success.
	if (!RegisterClassEx(&wcex))
		return 1;

	// Create the window.
	HWND hWnd = ::CreateWindowEx(
		0,
		TEXT("PROGRESSBARSAMPLE"),
		TEXT("ProgressBar samples"),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);

	// Validate window.
	if (!hWnd)
		return 1;


	HWND hDefaultProgressCtrl, 
		 hSmoothProgressCtrl, 
		 hVerticalProgressCtrl;


	// Create default progress bar.
	hDefaultProgressCtrl = ::CreateWindowEx(
		0,
		PROGRESS_CLASS,
		TEXT(""),
		WS_CHILD | WS_VISIBLE,
		20,
		20,
		450,
		30,
		hWnd,
		(HMENU)ID_DEFAULTPROGRESSCTRL,
		hInstance,
		NULL);

	::SendMessage(hDefaultProgressCtrl, PBM_SETPOS, (WPARAM)(INT)40, 0);


	// Create smooth progress bar.
	hSmoothProgressCtrl = ::CreateWindowEx(
		0,
		PROGRESS_CLASS,
		TEXT(""),
		WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		20,
		60,
		450,
		30,
		hWnd,
		(HMENU)ID_SMOOTHPROGRESSCTRL,
		hInstance,
		NULL);

	::SendMessage(hSmoothProgressCtrl, PBM_SETPOS, (WPARAM)(INT)40, 0);


	// Create vertical progress bar.
	hVerticalProgressCtrl = ::CreateWindowEx(
		0,
		PROGRESS_CLASS,
		TEXT(""),
		WS_CHILD | WS_VISIBLE | PBS_VERTICAL,
		20,
		100,
		30,
		100,
		hWnd,
		(HMENU)ID_VERTICALPROGRESSCTRL,
		hInstance,
		NULL);

	::SendMessage(hVerticalProgressCtrl, PBM_SETPOS, (WPARAM)(INT)40, 0);

	// Display the window.
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	// Main message loop.
	MSG msg;
	while (::GetMessage(&msg, hWnd, 0, 0) > 0)
		::DispatchMessage(&msg);

	// Unregister window class, freeing the memory that was
	// previously allocated for this window.
	::UnregisterClass(wcex.lpszClassName, hInstance);

	return (int)msg.wParam;
}