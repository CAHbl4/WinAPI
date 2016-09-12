#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <CommCtrl.h>
#include "resource.h"

HWND hProgress1, hProgress2;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		srand(time(0));
		hProgress1 = GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hProgress1, PBM_SETRANGE, 0, MAKELPARAM(0, 10)); // Установка интервала для индикатора 
		SendMessage(hProgress1, PBM_SETSTEP, 1, 0); // Установка шага приращения  индикатора 
		SendMessage(hProgress1, PBM_SETPOS, 0, 0); // Установка текущей позиции индикатора
		SendMessage(hProgress1, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255))); // Установка цвета фона индикатора
		SendMessage(hProgress1, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 255, 0))); // Установка цвета заполняемых прямоугольников

		hProgress2 = GetDlgItem(hWnd, IDC_PROGRESS2);
		SendMessage(hProgress2, PBM_SETRANGE, 0, MAKELPARAM(0, 10));
		SendMessage(hProgress2, PBM_SETSTEP, 1, 0);
		SendMessage(hProgress2, PBM_SETPOS, 0, 0);
		SendMessage(hProgress2, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 255, 0)));
		SendMessage(hProgress2, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 0, 255)));
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
			SetTimer(hWnd, 1, 100, NULL);
		return TRUE;
	case WM_TIMER:
	{
		SendMessage(hProgress1, PBM_STEPIT, 0, 0); // Изменение текущей позиции индикатора путём прибавления шага
		int n = rand() % 10;
		SendMessage(hProgress2, PBM_SETPOS, WPARAM(n), 0); // Установка текущей позиции индикатора
	}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
