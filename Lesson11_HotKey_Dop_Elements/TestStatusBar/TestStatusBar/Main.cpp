#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include<CommCtrl.h>

#pragma comment(lib,"comctl32")

#define ID_STATUS_BAR 201

HWND hCheck1, hCheck2, hEdit,hSpin,hStatus,hDialog;
HICON hIcon;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	hDialog = hWnd;
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
	{
						  hSpin = GetDlgItem(hWnd, IDC_SPIN1);
						  hEdit = GetDlgItem(hWnd, IDC_EDIT1);
						  hCheck1 = GetDlgItem(hWnd, IDC_CHECK1);
						  hCheck2 = GetDlgItem(hWnd, IDC_CHECK2);
						  // Установим диапазон счётчика
						  SendMessage(hSpin, UDM_SETRANGE32, 0, 100);
						  // Установим приятеля для счётчика
						  SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit), 0);
						  SetWindowText(hEdit, TEXT("0"));

						  // Создадим строку состояния
						  hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, 0, hWnd, ID_STATUS_BAR);

						  // Разделим строку состояния на отдельные секции
						  int parts[4] = { 40, 120, 240, -1 };
						  SendMessage(hStatus, SB_SETPARTS, 4, (LPARAM)parts);

						  // Для каждой секции установим текст и всплывающую подсказку
						  SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)TEXT("Счетчик: 0"));
						  SendMessage(hStatus, SB_SETTIPTEXT, 1, (LPARAM)TEXT("Счетчик: 0"));
						  SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)TEXT("Параметр 1: ОТКЛ"));
						  SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM)TEXT("Параметр 1: ОТКЛ"));
						  SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)TEXT("Параметр 2: ОТКЛ"));
						  SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM)TEXT("Параметр 2: ОТКЛ"));

						  // Загрузим иконку из ресурсов
						  hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));

						  // Установим иконку в первую секцию строки состояния
						  SendMessage(hStatus, SB_SETICON, 0, (LPARAM)hIcon);

						  // Установим цвет фона строки состояния
						  SendMessage(hStatus, SB_SETBKCOLOR, 0, (LPARAM)RGB(255, 200, 255));
	}
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CHECK1)
		{
			LRESULT lResult = SendMessage(hCheck1, BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED)
			{
				SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)TEXT("Параметр 1: ВКЛ"));
				SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM)TEXT("Параметр 1: ВКЛ"));
			}
			else
			{
				SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)TEXT("Параметр 1: ОТКЛ"));
				SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM)TEXT("Параметр 1: ОТКЛ"));
			}
		}
		if (LOWORD(wParam) == IDC_CHECK2)
		{
			LRESULT lResult = SendMessage(hCheck2, BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED)
			{
				SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)TEXT("Параметр 2: ВКЛ"));
				SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM)TEXT("Параметр 2: ВКЛ"));
			}
			else
			{
				SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)TEXT("Параметр 2: ОТКЛ"));
				SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM)TEXT("Параметр 2: ОТКЛ"));
			}
		}
		return TRUE;
	case WM_VSCROLL:
		{
					   // обработчик сообщения нажатия на одну из стрелок счётчика
					   int pos;
					   TCHAR buf[30];
					   pos = SendMessage(hSpin, UDM_GETPOS, 0, 0);
					   wsprintf(buf, TEXT("Счётчик: %d"), pos);
					   // отобразим состояние счётчика в строке состояния
					   SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)buf);
					   SendMessage(hStatus, SB_SETTIPTEXT, 1, (LPARAM)buf);

		}
		return TRUE;
	}
	return FALSE;
}
