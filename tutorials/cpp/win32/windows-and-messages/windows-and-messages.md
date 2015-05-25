# Windows and messages

##Purpose

The purpose of this tutorial is to take a deeper look at the WinMain function in order to understand how structured a Win32 application is. By the end of this tutorial, readers should be able to understand the concepts of message queues, window registration & creation, as well as the base of message loop and how all these operate to make an application work.

##Intended audience

This tutorial requires basic knowledge of Visual Studio. It is recommended to have read [Introduction](../introduction/introduction.md)  before proceeding. As stated in previous tutorials, readers should be proficients in C/C++, as this tutorial does not cover the C++ programming language.


##Objectives

* _Demestify the main function._
* _Window registration & creation analysis._  
* _Understanding the message loop._
* _Analyzing window procedure._

##Table of content

1. [Windows graphical environment](#windows-graphical-environment)
* [An overview of WinMain](#an-overview-of-winmain)
* [Window initialization](#window-initialization)
  1. [Window registration](#window-registration)
  * [Window creation](#window-creation)
* [Accelerator table](#accelerator-table)
* [The message loop](#the-message-loop)
* [The window procedure](#the-window-procedure)
* [Conclusion](#conclusion)

---

#Windows graphical environment

In the windows graphical environment, everything is a window. Even the desktop area is part of a window. This window is more precisely known as the desktop window. Everytime you run an application that displays one or more windows, all of it's windows become children of the desktop window.


![](images/window-hierarchy.png)



#An overview of WinMain


```c

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_INTRODUCTION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INTRODUCTION));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


```


#Window initialization

##Window registration


Before a window can be created, it needs to be registered in order to be identified during runtime by messages and events. In order to understand the registration process, let's head to `MyRegisterClass` definition.


```c

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	  = WndProc;
	wcex.cbClsExtra	   = 0;
	wcex.cbWndExtra	   = 0;
	wcex.hInstance	    = hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INTRODUCTION));
	wcex.hCursor		  = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	 = MAKEINTRESOURCE(IDC_INTRODUCTION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		  = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

```

To register a window, we must begin by defining the window class attributes. These are attributes to be shared by all windows that will use this kind of class. It is important to note that a window class **_must_** be **_unique_**.

###The WNDCLASSEX structure


```c

typedef struct tagWNDCLASSEXW {
    UINT        cbSize;
    /* Win 3.x*/
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
    /* Win 4.0*/
    HICON       hIconSm;
} WNDCLASSEXW, *PWNDCLASSEXW, NEAR *NPWNDCLASSEXW, FAR *LPWNDCLASSEXW;

```

|Name|Description|
|:--|:--|
|`cbSize`|The size in bytes of `WNDCLASSEX`|
|`style`|The style of the window|
|`lpfnWndProc`|A pointer to a WNDPROC callback to use as a message listener|
|`cbClsExtra`|A set of additional flag values|
|`cbWndExtra`|A set of additional flag values|
|`hInstance`|A handle to the current application instance|
|`hIcon`|A handle to an icon|
|`hCursor`|A handle to a cursor|
|`hbrBackground`|A handle to a brush color|
|`lpszMenuName`|The Menu name|
|`lpszClassName`|This window's class name|

---

> ***Reminder***
>
> Windows Data types
>
> |Name|Definition|
> |:--|:--|
> |LPCWSTR|`typedef const wchar_t* LPCWSTR`|
> |LPCWSTR|`typedef const wchar_t* LPCWSTR`|
>

###RegisterClassEx

```c
return RegisterClassEx(&wcex);
```

`RegisterClassEx` is a function that takes a pointer to a `WNDCLASSEX` structure and returns a unique identifier for the window. If the function fails, the return value is zero.


#####Reasons why RegisterClassEx would not work

* `cbSize` is not specified or improperly initialized. The recommended way is to set `cbSize` to `sizeof(WNDCLASSEX)`.
* `lpszClassName` is already registered, and thus is causing a failure to avoid duplicate classes.
* `hInstance` is not a valid application instance, or is uninitialized.
* `hbrBackground` is an invalid `HANDLE` value. The default value is `(HBRUSH)(COLOR_WINDOW+1)`.


##Window creation

After the window registration, the window needs to be created. Let us proceed to the function `InitInstance`.

```c

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
```


This variable `hWnd`, is a handle to our main window. it is initialized by `CreateWindow`, which is used to create a window of a particuliar style at a given position. If a window parent is specified, the newly created window will become a child of the parent.

All present parameters in `CreateWindow` are the same as those found in `CREATESTRUCT`.  
Here is a closer look at this particuliar structure.

###The CreateStruct Structure

```c
typedef struct tagCREATESTRUCTA {
    LPVOID      lpCreateParams;
    HINSTANCE   hInstance;
    HMENU       hMenu;
    HWND        hwndParent;
    int         cy;
    int         cx;
    int         y;
    int         x;
    LONG        style;
    LPCSTR      lpszName;
    LPCSTR      lpszClass;
    DWORD       dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;
```

|Name|Description|
|:--|:--|
|`lpCreateParams`|An argument that can be passed for futher use in the `WndProc` function|
|`hInstance`|The instance of the associated application|
|`hMenu`|A handle to a menu|
|`hwndParent`|A handle to a window to use as parent|
|`cy`|The height of the window|
|`cx`|The width of the window|
|`x`|The left position of the window|
|`y`|The top position of the window|
|`style`|The style of the window|
|`lpszName`|The name of the window (title)|
|`lpszClass`|The window's classname. This must match `wcex.lpszClassName` in `WNDCLASSEX`|
|`dwExStyle`|An extended window style - **Unused in this example!**|


#Accelerator table

This instruction is used to load an accelerator table from a resource file.

```c

hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INTRODUCTION));

```

I will not explain in depth resource files, as resources will be explained in further tutorials, but for a quick overview: An accelerator table is used to bind keyboard combinaisons to application commands.

By default, template applications use automatically generated accelerator tables, but keep in mind that these are not required at all.


#The message loop

Now that the main window is created and setup, it is time to setup the main loop of our application, which will take care of processing messages and events. Before demonstrating the code, we will take a look at the concept of sending and recieving events in an event-driven architecture.


![](images/message-queue.png)

To begin with, the system checks if there are pending messages in the message queue. If such a condition is met, then the system translates and dispatches the message to the appropriate window, which is, in this case, our main window. Each window is given a procedure. This procedure is represented by `lpfnWndProc` in the `WNDCLASSEX` structure. This procedure is called by with the window handle to which it is associated, the message type, and additionally, with up to two parameters, `wParam`, `lParam`. The window procedure is responsible for doing tasks, often based on the message type. If the message type is the quit message, the function will return with negative result, causing the message loop to end. If this message differs from quitting, then the system will return to the message queue to process the next message, or wait until it recieves new notifications.


In order to process messages continuously, we need to create a loop. This loop, called the message loop. Here is the code from `WinMain`.

```c

// Main message loop:
while (GetMessage(&msg, NULL, 0, 0))
{
  if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

```

####GetMessage

```c
BOOL WINAPI GetMessage(
  _Out_    LPMSG lpMsg,
  _In_opt_ HWND  hWnd,
  _In_     UINT  wMsgFilterMin,
  _In_     UINT  wMsgFilterMax
);
```

The `GetMessage` function is used to retrieve pending messages in the message queue, waiting for a particuliar event to occur, such as mouse clicks, window resizing, focus loss, etc..


####TranslateAccelerator

```c
int WINAPI TranslateAccelerator(
  _In_ HWND   hWnd,
  _In_ HACCEL hAccTable,
  _In_ LPMSG  lpMsg
);
```


As it recieves a message, the function `TranslateAccelerator` is used to determine whether this message was triggered by an accelerator handle. If this is the case, then the accelerator will handle the message itself and redirect it to the proper commands.

####TranslateMessage

```c
BOOL WINAPI TranslateMessage(
  _In_ const MSG * lpMsg
  );
```


If the application needs to read from user input such as keyboard/mouse, The `TranslateMessage` function is used translate virtual-key messages into character messages.

####DispatchMessage

```c
LRESULT WINAPI DispatchMessage(
  _In_ const MSG * lpmsg
);
```

This function, `DispatchMessage`, is used to dispatch messages to a window procedure. In this case, the window procedure is represented by attribute `lpfnWndProc` from `WNDCLASSEX`, WndProc.

##Message & Event callback

This is the window procedure, which is called when a particuliar event is sent this window. To begin with, let us have a look at the function's declaration and parameters.

```c
LRESULT CALLBACK WindowProc(
 HWND hwnd,
 UINT  uMsg,
 WPARAM wParam,
 LPARAM lParam
);
```

|Name|Description|
|:--|:--|
|hwnd|A handle to the window itself|
|uMsg|A system-defined message|
|wParam|A message parameter|
|lParam|A message parameter|


The first parameter, `hwnd`, represents the current window being processed. This is represented by `hwnd` in the `InitWindow`.

The second parameter, `uMsg`, is a system-defined message. This is used to determine the nature of the event, .i.e: Keyboard input, mouse input, window focus acquisition/loss, etc...

The remaining parameters `wParam` & `lParam` are message parameters that may contain data/values based on the current value of `uMsg`, the message type.

Now it is time to examine the definition of `WndProc`, the window procedure function.


```c

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

```

At a first look, this function looks confusing, but it is relatively simple to understand. As simplicity matters in these introductory tutorials, the definition of each case will be separated.

####WM_COMMAND

This message is sent whenever a user interation occurs, such as menu item selection, or when a parent recieves a notification from a child window.

```c
case WM_COMMAND:
  wmId    = LOWORD(wParam);
  wmEvent = HIWORD(wParam);
  // Parse the menu selections:
  switch (wmId)
  {
  case IDM_ABOUT:
    ...
  case IDM_EXIT:
    ...
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  break;
```

One important thing to note here is the use of macros `LOWORD` & `HIWORD`.

```c
wmId    = LOWORD(wParam);
wmEvent = HIWORD(wParam);
```

Before explaining the main purpose of both macros, we must comprehend what `wParam` is. `wParam` is a parameter of type `WPARAM`. The type `WPARAM` is an alias to a 32 bits unsigned integer. If targeting a 64 bits architecture, such as Windows x64, this will constitute an alias to a 64 bits integer, which is equivalent to an `unsigned long long`, or `unsigned long long int`.

Assuming readers are familiar with binary representation, `LOWORD` & `HIWORD` are macros for retrieving specific bits of `wParam`. Using bitwise operators, the `LOWORD` macro can be seen as:

```c
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
```

The `HIWORD` macro is defined as:

```c
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
```

In short, `LOWORD` simply performs logical conjunction (AND) operation with value 0xffff which clears the upper 16 bits, leaving only the lower part unaffected.

`HIWORD`, itself includes one extra before `LOWORD`: to use the right shift operators `>>` to shift the upper part to the right, thus overriding the lower 16 bits, and then applying logical conjunction to clear the upper part.

**Note:** _We must ensure to clear the upper part again, othewise it could result in improper values._


Once retrieved, this value will tell us the message ID, where prefixes such as `IDM` are used as naming conventions to indicate that this represents a message ID. This leads us to an other conditional branch with two cases, `IDM_ABOUT` and `IDM_EXIT`.


```c
case WM_COMMAND:
  wmId    = LOWORD(wParam);
  wmEvent = HIWORD(wParam);
  // Parse the menu selections:
  switch (wmId)
  {
  case IDM_ABOUT:
    ...
  case IDM_EXIT:
    ...
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  break;
```

######IDM_ABOUT

When users click the close button(X) at the top right corner, this causes the window to send a message `WM_COMMAND` with argument `IDM_ABOUT` passed to `wParam` as the low word (or low part), which is retrieved with macro `LOWORD`. If the value corresponds to `IDM_ABOUT`, then `DialogBox` is called and initialize a dialog that displays information about the authors of the application. I will not explain how `DialogBox` works for simplicity purposes. This will be covered in further tutorials.

```c
case IDM_ABOUT:
  DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
  break;

```

######IDM_EXIT

When users click the close button(X) at the top right corner, this causes the window to send a message `WM_COMMAND` with argument `IDM_EXIT` passed to `wParam` as the low word (or low part), which is retrieved with macro `LOWORD`. If the value corresponds to `IDM_EXIT`, then the `DestroyWindow` function is called, which will then send a WM_DESTROY message to the window, as seen further in this tutorial.

```c
case IDM_EXIT:
  DestroyWindow(hWnd);
  break;
```

---

####WM_PAINT

The `WM_PAINT` identifier is used to describe the paint event. This event occurs everytime a window is redrawn. The function `BeginPaint` and `EndPaint` are used to specify both start and end of drawing process. On return, all the drawing that was done will be sent to screen.

```c
case WM_PAINT:
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
	break;
```

####WM_DESTROY

This command is called whenever the `DestroyWindow` function is called. For example, whenever a user clicks the close button of the window, at the upper right corner (windows applications), `DestroyWindow` is called. By doing so, a message `WM_DESTROY` is then sent to the window handle.

Call of `PostQuitMessage(0)` is used to indicate that the window is terminating, thus

```c
case WM_DESTROY:
        PostQuitMessage(0);
        break;
```


######default

In the default case, a function named `DefWindowProc` is used as a default return result.

```c
default:
  return DefWindowProc(hWnd, message, wParam, lParam);
```

This function simply calls the default window procedure to process all messages that were not caught in `WndProc`. By the end of this function, this leads us back to the message loop, which will continue process messages that are in the message queue, or wait until a message is recieved.


---

#Conclusion

From there, readers should be familiar with the basics of a Win32 API. Readers should have a fair understanding from a conceptual point of view of Win32's event & message processing and how the main loop is interacting with these. Readers are encouraged to read this tutorial again to ensure correct understanding, as further tutorials will cover and expand concepts viewed throughout this lecture.

---


[Previous](../introduction/introduction.md) | [Index](../../index.md)
