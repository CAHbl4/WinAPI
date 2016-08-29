#define CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include<tchar.h>
#include "resource.h"
#include <ctime>

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPTSTR lCmdCommand, INT iCmd)
{
	hInst = hInstance;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1, hStart, hCheckBox;

	switch (message)
	{
		//получение дескрипторов в момент создания диалогового окна
	case WM_INITDIALOG:
		hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hStart = GetDlgItem(hWnd, IDC_BUTTON2);
		hCheckBox = GetDlgItem(hWnd, IDC_CHECK1);
		//устанавливаем программно флажок посылкой сообщения BM_SETCHECK
		SendMessage(hCheckBox, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		return TRUE;
	case WM_COMMAND:
		//если нажали кнопку start(stop)
		if (LOWORD(wParam) == IDC_BUTTON2)
		{
			TCHAR str[10];
			//получаем надпись кнопки
			GetWindowText(hStart, str, 10);
			//проверяем, что написано
			if (!lstrcmp(str, TEXT("Start")))
			{
				SetWindowText(hStart, TEXT("Stop"));
				//запускаем таймер
				SetTimer(hWnd, 1, 1000, NULL);

			}
			else
			{
				SetWindowText(hStart, TEXT("Start"));
				KillTimer(hWnd, 1);
			}

		}
		return TRUE;
		//обработка сообщений от таймера
	case WM_TIMER:
	{
		static time_t t;
		static TCHAR str[100];
		t = time(NULL);
		// получаем системное время и сохраняем 
		struct tm DateTime;
		localtime_s(&DateTime,&t);
		//проверяем установлен ли CheckBox
		LRESULT lResult = SendMessage(hCheckBox, BM_GETCHECK, 0, 0);
		//если флаг установлен
		if (lResult==BST_CHECKED)
			//формируем строку с отображением секунд
			_tcsftime(str, 100, TEXT("%H:%M:%S  %d.%m.%Y  %A"), &DateTime);
		else
			//формируем строку без отображения секунд
			_tcsftime(str, 100, TEXT("%H:%M  %d.%m.%Y  %A"), &DateTime);
		//выводим строку в Button1
		SetWindowText(hButton1, str);
	}
		return TRUE;


	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}


	return FALSE;
}
