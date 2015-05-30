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

// Include required for resources
#include "resource.h"

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
_tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nShowCmd)
{
	const size_t MAX_LOADSTRING = 100;

	TCHAR className[MAX_LOADSTRING];
	TCHAR title[MAX_LOADSTRING];
	HCURSOR cursor;
	HICON icon, iconSmall;

	::LoadString(hInstance, IDS_MYAPP_CLASS, className, MAX_LOADSTRING);
	::LoadString(hInstance, IDS_MYAPP_TITLE, title, MAX_LOADSTRING);

	cursor		= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_MYAPP_POINTER));
	icon		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYAPP_ICON));
	iconSmall	= (HICON)LoadImage( 
		hInstance, // Handle to the module containing the embedded resource.
		MAKEINTRESOURCE(IDI_MYAPP_ICON_SMALL),  // Small icon.
		IMAGE_ICON,  // Specifies the image type.
		16, // The width of the image to be loaded.
		16, // The height of the image to be loaded.
		0); // The 


	// Setup window class attributes.
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize			= sizeof(wcex);	// WNDCLASSEX size in bytes
	wcex.style			= CS_HREDRAW | CS_VREDRAW;		// Window class styles
	wcex.lpszClassName	= className;	// Window class name
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);	// Window background brush color.
	wcex.hCursor		= cursor;		// Window cursor
	wcex.lpfnWndProc	= WndProc;		// Window procedure associated to this window class.
	wcex.hInstance		= hInstance;	// The application instance.
	wcex.hIcon			= icon;			// Application icon.
	wcex.hIconSm		= iconSmall;	// Application small icon.

	// Register window and ensure registration success.
	if (!RegisterClassEx(&wcex))
		return 1;

	// Setup window initialization attributes.
	CREATESTRUCT cs;
	ZeroMemory(&cs, sizeof(cs));

	cs.x = 0;	// Window X position
	cs.y = 0;	// Window Y position
	cs.cx = 640;	// Window width
	cs.cy = 480;	// Window height
	cs.hInstance = hInstance; // Window instance.
	cs.lpszClass = wcex.lpszClassName;		// Window class name
	cs.lpszName = title;	// Window title
	cs.style = WS_OVERLAPPEDWINDOW;		// Window style

	// Create the window.
	HWND hWnd = ::CreateWindowEx(
		cs.dwExStyle,
		cs.lpszClass,
		cs.lpszName,
		cs.style,
		cs.x,
		cs.y,
		cs.cx,
		cs.cy,
		cs.hwndParent,
		cs.hMenu,
		cs.hInstance,
		cs.lpCreateParams);

	// Validate window.
	if (!hWnd)
		return 1;

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