#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPTSTR lpszCmdLine, int nCmdShow) {
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if (wParam == IDOK || wParam == IDCANCEL)
			EndDialog(hWnd, 0);
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}