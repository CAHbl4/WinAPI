#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <strsafe.h>


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
TCHAR sz[100];

TCHAR * LoadStringFromResource(UINT id)
{
	LoadString(0, id, sz, 100);
	size_t size = lstrlen(sz) + 1;
	TCHAR * result = (TCHAR*)malloc(size);
	StringCchCopy(result, size, sz);
	return result;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow) {
	TCHAR * mbTitle = LoadStringFromResource(IDS_QUESTION_TITLE);
	TCHAR * mbMessage = LoadStringFromResource(IDS_QUESTION);
	if (MessageBox(0, mbTitle, mbMessage, MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	}
	else {
		
	}

	free(mbTitle);
	free(mbMessage);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CLOSE:
			EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
