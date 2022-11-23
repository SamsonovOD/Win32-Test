#include <windows.h>
#include "resource.h"
#include "functions.h"

const char WND_CLASSNAME[] = "WindowClass";
const char WND_CAPTION[] = "Window Caption";
const int WND_WIDTH = 640;
const int WND_HEIGHT = 480;
const LPSTR WND_ICON = MAKEINTRESOURCE(IDI_MYICON);

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

        case WM_CREATE: {
			drawBitmap(hwnd);
			drawTextmap(hwnd);
            break;
		}

		case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+2));

//			HICON hIcon = LoadImage(NULL, "icon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
//			DrawIcon(hdc, 10, 20, hIcon);

            EndPaint(hwnd, &ps);
			return 0;
        }

		/* Upon window close */
		case WM_CLOSE: {
			int mb = showPopup(hwnd, "Question title", "Really quit?");
			if (mb == IDOK) {
				DestroyWindow(hwnd);
			}
			// Cancelled.
			return 0;
		}

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));


	wc.cbSize		 = sizeof(WNDCLASSEX); /* The size of the structure. */
	wc.hInstance	 = hInstance; /* Handle to application instance */
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.lpszClassName = WND_CLASSNAME; /* Name to identify the class with. */
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW); /* Cursor */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); /* Background Brush */
	wc.hIcon		 = LoadIcon(hInstance, WND_ICON); /* Large (32x32) icon, Alt+Tab */
	wc.hIconSm		 = LoadIcon(hInstance, WND_ICON); /* Small (16x16) icon, title and taskbar */

	if(!RegisterClassEx(&wc)) {
		MessageBox(
			NULL,
			"Window Registration Failed!",
			"Error!",
			MB_ICONEXCLAMATION | MB_OK
		);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, /* Optional window styles */
		wc.lpszClassName, /* Window class */
		WND_CAPTION, /* Window title */
		WS_VISIBLE | WS_OVERLAPPEDWINDOW, /* Window style */
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		WND_WIDTH, /* width */
		WND_HEIGHT, /* height */
		NULL, /* Parent window */
		NULL, /* Menu */
		hInstance, /* Instance handle */
		NULL /* Additional application data */
	);

	if(hwnd == NULL) {
		MessageBox(
			NULL,
			"Window Creation Failed!",
			"Error!",
			MB_ICONEXCLAMATION|MB_OK
		);
		return 0;
	}

	//ShowWindow(hwnd, nCmdShow);
	//UpdateWindow(hwnd);

	/* Message loop	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
