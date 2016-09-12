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
	static HWND hList1, hList2, hEditAdd, hEditFind, hButtonAdd, hButtonFind, hButtonDelete, hButtonClear, hButton5;
	int index;
	switch (message)
	{
	case WM_INITDIALOG:
		//получение дескрипторов
		hList1 = GetDlgItem(hWnd, IDC_LIST1);
		hList2 = GetDlgItem(hWnd, IDC_LIST2);
		hEditAdd = GetDlgItem(hWnd, IDC_EDIT1);
		hEditFind = GetDlgItem(hWnd, IDC_EDIT2);
		hButtonAdd = GetDlgItem(hWnd, IDC_BUTTON1);
		hButtonFind = GetDlgItem(hWnd, IDC_BUTTON2);
		hButtonDelete = GetDlgItem(hWnd, IDC_BUTTON3);
		hButtonClear = GetDlgItem(hWnd, IDC_BUTTON4);

		//формирование списка
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Реал"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("ФК Гомель"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Атлетико"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Челси"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Спарта"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("Зенит"));

		//формирование списка с множественным выбором
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Челси"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Спарта"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Зенит"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Реал"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("ФК Гомель"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Манчестер"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Арсенал"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Динамо"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Спартак"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("Локоматив"));
		
		return TRUE;


		//обработка нажатия кнопок
	case WM_COMMAND:
	{
					   TCHAR str[100];
					   switch (LOWORD(wParam))
					   {
					   case IDC_BUTTON1:
						   //считываем название клуба
						   GetWindowText(hEditAdd, str, 100);
						   //добавляем в список
						   SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)str);
						   break;
					   case IDC_BUTTON4:
						   //очищаем список
						   SendMessage(hList1, LB_RESETCONTENT, 0, 0);
						   break;
					   case IDC_BUTTON2:
					   {//удаление из списка
										   //получаем индекс выделенного элемента
										   index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
										   //если был выбран эемент
										   if (index != LB_ERR)
											   //удаляем
											   SendMessage(hList1, LB_DELETESTRING, (WPARAM)index, 0);
					   }
						   break;
					   case IDC_BUTTON3:
						   //поиск элемента
						   //считываем название клуба из Edit2
						   GetWindowText(hEditFind, str, 100);
						   //поиск с подсветкой
						   index = SendMessage(hList1, LB_SELECTSTRING, 0, (LPARAM)str);
						   if (index == LB_ERR)
							   MessageBox(hWnd, TEXT("Такого клуба нет в списке"), 0, MB_OK | MB_ICONERROR);
						   break;
					   case IDC_BUTTON5:
					   {
										   //определяем количество выделенных элементов
										   int count = SendMessage(hList2, LB_GETSELCOUNT, 0, 0);
										   // выделим память необходимого размера для хранения индексов выбранных элементов списка
										   int *p = new int[count];
										   // Заполним динамический массив индексами выделенных элементов списка 
										   SendMessage(hList2, LB_GETSELITEMS, count, LPARAM(p));
										   //выводим назание выбранных элементов
										   for (int i = 0; i < count; i++)
										   {
											   //получаем название элемента
											   SendMessage(hList2, LB_GETTEXT, (WPARAM)p[i], (LPARAM)str);
											   MessageBox(hWnd, str, TEXT("Множественный выбор"), MB_OK | MB_ICONINFORMATION);
										   }

										   delete[] p;
					   }
						   break;
					   }
	}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
