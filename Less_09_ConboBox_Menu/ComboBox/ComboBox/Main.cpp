#include <windows.h>
#include <tchar.h>
#include "resource.h"


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hCombo, hList, hCheck, hEdit;
	switch (message)
	{
	case WM_INITDIALOG:
		hCombo = GetDlgItem(hWnd, IDC_COMBO1);
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hCheck = GetDlgItem(hWnd, IDC_CHECK1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);

		//создаем элементы списка
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Зима"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Весна"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Лето"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Осень"));
		return TRUE;
	case WM_COMMAND:
		//сообщение при выборе элемента из раскрывающего списка
		if (LOWORD(wParam) == IDC_COMBO1 && HIWORD(wParam) == CBN_SELCHANGE)
		{
			// Получим индекс выбранного элемента ComboBox
			int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			//очищаем список месяцев
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			switch (index)
			{
			case 0:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Декабрь"));
				SendMessage(hList, LB_SETITEMDATA, 0, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Январь"));
				SendMessage(hList, LB_SETITEMDATA, 1, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Февраль"));
				SendMessage(hList, LB_SETITEMDATA, 2, 28);
				break;
			case 1:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Март"));
				SendMessage(hList, LB_SETITEMDATA, 0, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Апрель"));
				SendMessage(hList, LB_SETITEMDATA, 1, 30);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Май"));
				SendMessage(hList, LB_SETITEMDATA, 2, 31);
				break;
			case 2:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Июнь"));
				SendMessage(hList, LB_SETITEMDATA, 0, 30);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Июль"));
				SendMessage(hList, LB_SETITEMDATA, 1, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Август"));
				SendMessage(hList, LB_SETITEMDATA, 2, 31);
				break; 
			case 3:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Сентябрь"));
				SendMessage(hList, LB_SETITEMDATA, 0, 30);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Октябрь"));
				SendMessage(hList, LB_SETITEMDATA, 1, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("Ноябрь"));
				SendMessage(hList, LB_SETITEMDATA, 2, 30);
				break;
			}
		}
		if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE)
		{
			// Получим индекс выбранного элемента ListBox
			int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			TCHAR str[20];
			// выбираем количество дней
			int day=SendMessage(hList, LB_GETITEMDATA, index, 0);
			// Снимем текст с выбранного элемента списка
			SendMessage(hList, LB_GETTEXT, index, LPARAM(str));
			if (!lstrcmp(str, TEXT("Февраль")))
			{	// Проверяем, високосный год или нет
				int status = SendMessage(hCheck, BM_GETCHECK, 0, 0);
				if (status == BST_CHECKED)
					day++;
			}
			wsprintf(str, TEXT("%d"), day);
			SetWindowText(hEdit, str);


		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}

