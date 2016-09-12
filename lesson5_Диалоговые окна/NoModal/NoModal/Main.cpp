#include <Windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPTSTR lpszCmdLine,
	int nCmdShow)
{
	MSG msg;
	// создаём главное окно приложения на основе немодального диалога
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	// Отображаем окно	
	ShowWindow(hDialog, nCmdShow);


	//Запускаем цикл обработки сообщений
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		if (wParam == IDOK)
		{
			//закрываем окно
			DestroyWindow(hWnd);
			//прекращаем работу приложения
			PostQuitMessage(0);
		}
		return TRUE;
	case WM_CLOSE:
		//закрываем окно
		DestroyWindow(hWnd);
		//прекращаем работу приложения
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

