#include <windows.h>

void drawBitmap(HWND hwnd) {
	HANDLE hBitmap = LoadImageW(
		NULL,
		L"bmp_24.bmp",
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
	);
	HWND hsti = CreateWindowW(
		L"Static",
		L"",
		WS_CHILD | WS_VISIBLE | SS_BITMAP,
		5, 5, 200, 300,
		hwnd,
		(HMENU) 1,
		NULL,
		NULL
	);
	SendMessage(hsti, STM_SETIMAGE, (WPARAM) IMAGE_BITMAP, (LPARAM) hBitmap);
}

void drawTextmap(HWND hwnd) {
	const wchar_t* string = L"According to all known laws of aviation,\n\
there is no way a bee should be able to fly.\n\
It's wings are too small to get its fat little body off the ground.\n\
The bee, of course, flies anyway, because bees don't care what humans think is impossible";
    CreateWindowW(
		L"Static",
		string,
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        250, 5, 200, 300,
        hwnd,
		(HMENU) 1,
		NULL,
		NULL
	);
}

int showPopup(HWND hwnd, char* title, char* message) {
	MessageBox(
		hwnd,
		message,
		title,
		MB_ICONQUESTION | MB_OKCANCEL
	);
}
