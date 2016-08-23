#include <Windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPTSTR  lpszCmdLine, int nCmdShow)
{
	// создаём главное окно приложения на основе модального диалога
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
};

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1,hButton2,hButton3,hStatic;
	switch (message)
	{
	case WM_INITDIALOG:
		//создание кнопки
		hButton3 = CreateWindow(TEXT("Button"), TEXT("Programm Button"), WS_CHILD | WS_VISIBLE, 20, 100, 150, 50, hWnd, NULL, NULL, 0);
		//создание статика
		hStatic = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE, 200, 100, 150, 50, hWnd, NULL, NULL, 0);
		//получение дескрипторов кнопок по идентификатору
		hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hButton2 = GetDlgItem(hWnd, IDC_BUTTON2);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			MessageBox(hWnd, TEXT("Нажата первая кнопка!!!"), TEXT("Работа с кнопками"), MB_OK);
			//установка текста в кнопке 3
			SetWindowText(hButton3, TEXT("Нажми меня!!!"));
		}
		else if (LOWORD(wParam) == IDC_BUTTON2)
			MessageBox(hWnd, TEXT("Нажата вторая кнопка!!!"), TEXT("Работа с кнопками"), MB_OK);
		else if ((HWND)lParam == hButton3)
			SetWindowText(hStatic, TEXT("Вы нажали кнопку 3"));

		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}