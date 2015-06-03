// Button.cpp

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

#define ID_DEFPUSHBUTTON	401
#define ID_PUSHBUTTON		402
#define ID_CHECKBOX			403
#define ID_RADIOBUTTON1		404
#define ID_RADIOBUTTON2		405
#define ID_RADIOBUTTON3		406

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

	case WM_COMMAND:
	{
		HWND hButtonWnd;
		INT	 wId,
			 wNotify;

		wId			= (INT)LOWORD(wParam);
		wNotify		= (INT)HIWORD(wParam);
		hButtonWnd	= (HWND)lParam;

		switch (wNotify)
		{

		case BN_CLICKED:
			{
				static LPCTSTR szCaption = TEXT("Information");
				static UINT uFlags = MB_OK | MB_ICONINFORMATION;

				switch (wId)
				{
				case ID_DEFPUSHBUTTON:
					MessageBox(NULL, TEXT("ID_DEFPUSHBUTTON"), szCaption, uFlags);
					break;
				case ID_PUSHBUTTON:
					MessageBox(NULL, TEXT("ID_PUSHBUTTON"), szCaption, uFlags);
					break;
				case ID_CHECKBOX:
					MessageBox(NULL, TEXT("ID_CHECKBOX"), szCaption, uFlags);
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	break;

	default:
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK GroupBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
	UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{

	switch (uMsg)
	{
	case WM_COMMAND:
		{
			INT wId, wNotify;
			wId			= (INT)LOWORD(wParam);
			wNotify		= (INT)HIWORD(wParam);

			switch (wNotify)
			{
			case BN_CLICKED:
				{
					static LPCTSTR szCaption = TEXT("Information");
					static UINT uFlags = MB_OK | MB_ICONINFORMATION;

					switch (wId)
					{
					case ID_RADIOBUTTON1:
						MessageBox(NULL, TEXT("ID_RADIOBUTTON1"), szCaption, uFlags);
						break;
					case ID_RADIOBUTTON2:
						MessageBox(NULL, TEXT("ID_RADIOBUTTON2"), szCaption, uFlags);
						break;
					case ID_RADIOBUTTON3:
						MessageBox(NULL, TEXT("ID_RADIOBUTTON3"), szCaption, uFlags);
						break;
					default:
						break;
					}
				}
				break;

			default:
				break;
			}
		}
		break;

	default:
		return DefSubclassProc(hWnd, uMsg, wParam, lParam);
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
	// Setup window class attributes.
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize			= sizeof(wcex);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpszClassName	= TEXT("BUTTONSAMPLE");
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.hCursor		= LoadCursor(hInstance, IDC_ARROW);
	wcex.lpfnWndProc	= WndProc;
	wcex.hInstance		= hInstance;	

	// Register window and ensure registration success.
	if (!RegisterClassEx(&wcex))
		return 1;

	// Create the window.
	HWND hWnd = ::CreateWindowEx(
		0, 
		TEXT("BUTTONSAMPLE"),
		TEXT("Button samples"),
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


	HWND hButton, hGroupBox;




	// Create a default push button.
	hButton = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Default Push Button"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20,
		20,
		150,
		28,
		hWnd,
		(HMENU)ID_DEFPUSHBUTTON,
		hInstance,
		NULL);

	// Create a push button.
	hButton = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Push Button"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20,
		60,
		128,
		28,
		hWnd,
		(HMENU)ID_PUSHBUTTON,
		hInstance,
		NULL);

	// Create a check box.
	hButton = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Checkbox"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		20,
		100,
		150,
		28,
		hWnd,
		(HMENU)ID_CHECKBOX,
		hInstance,
		NULL);


	// Create a group box
	hGroupBox = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Group box"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20,
		140,
		168,
		124,
		hWnd,
		NULL,
		hInstance,
		NULL);

	if (!::SetWindowSubclass(hGroupBox, GroupBoxProc, 0, 0))
		return 1;

	// Create radio button 1.
	hButton = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Radio button 1"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | UDS_WRAP,
		20,
		20,
		128,
		28,
		hGroupBox,
		(HMENU)ID_RADIOBUTTON1,
		hInstance,
		NULL);

	// Create radio button 2.
	hButton = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Radio button 2"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		20,
		48,
		128,
		28,
		hGroupBox,
		(HMENU)ID_RADIOBUTTON2,
		hInstance,
		NULL);

	// Create radio button 3.
	hButton = ::CreateWindowEx(
		0,
		WC_BUTTON,
		TEXT("Radio button 3"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		20,
		76,
		128,
		28,
		hGroupBox,
		(HMENU)ID_RADIOBUTTON3,
		hInstance,
		NULL);


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