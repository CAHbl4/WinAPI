#include <windows.h>
#include <tchar.h>
#include "resource.h"

HWND hLogin, hPassword;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hDialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	//загрузка ресурса
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	ShowWindow(hDialog, nCmdShow);
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (!TranslateAccelerator(hDialog, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu;
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;

	case WM_INITDIALOG:
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		// Присоединим меню к главному окну приложения
		SetMenu(hWnd, hMenu);
		return TRUE;

	case WM_COMMAND:
	{
		TCHAR str1[300], str2[50];
		HMENU hMenu = GetMenu(hWnd);
		GetMenuString(hMenu, LOWORD(wParam), str2, 50, MF_BYCOMMAND);
		if (HIWORD(wParam) == 1)
			_tcscpy_s(str1,300, TEXT("Пункт меню выбран с помощью акселератора\n"));
		else if (HIWORD(wParam) == 0)
			_tcscpy_s(str1,300, TEXT("Пункт меню выбран при непосредственном обращении к меню\n"));
		_tcscat_s(str1,300, str2);
		MessageBox(hWnd, str1, TEXT("Меню и акселераторы"), MB_OK | MB_ICONINFORMATION);
	}
		return TRUE;
	}
	return FALSE;
}
