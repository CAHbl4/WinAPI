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
	//дескрипторы элементов управления
	static HWND hButton1, hButton2, hEdit1, hEdit2, hCheck1, hCheck2;
	//дескрипторы меню
	static HMENU  hMenu, hSubMenu, hSubMenu2, hSubMenu3;
	//код состояния элементов управления
	static DWORD dwButtonState = MF_CHECKED, dwEditState = MF_CHECKED, dwCheckboxState=MF_CHECKED;
	
	switch (message)
	{
	case WM_INITDIALOG:
		//получаем дескрипторы элементов управления
		hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
		hCheck1 = GetDlgItem(hWnd, IDC_CHECK1);

		hButton2 = GetDlgItem(hWnd, IDC_BUTTON2);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
		hCheck2 = GetDlgItem(hWnd, IDC_CHECK2);

		// Загрузим меню из ресурсов приложения
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		//загружаем подменю
		hSubMenu = GetSubMenu(hMenu, 0);
		hSubMenu2 = GetSubMenu(hSubMenu, 0);
		hSubMenu3 = GetSubMenu(hSubMenu, 1);
		
		//устанавливаем флажки в CheckBox
		SendMessage(hCheck1, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		SendMessage(hCheck2, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

		//устанавливаем единичный выбор в группе2 меню
		//1- дескриптор подменю
		//2- начальный индекс элемента, входящего в группу
		//3- конечный индекс элемента
		//4- индекс элемента, который будет отмечен
		CheckMenuRadioItem(hSubMenu3, 0, 2, 1, MF_BYPOSITION);
		return TRUE;

	//сообщение при вызове котекстного меню
	case WM_CONTEXTMENU:
		//1- дескриптор подменю
		//2- выравнивание
		//3- координата x
		//4- координата y
		//5- значение 0
		//6- дескриптор окна
		//7- не используется
		TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);

		return TRUE;

		//обработка сообщений от элементов управления
	case WM_COMMAND:
	{
					   int id = LOWORD(wParam);
					   //команды поступают о первой группы меню
					   if (id >= ID_40003&&id <= ID_40005)
					   {
						   switch (id)
						   {
							   //первый пункт меню
						   case ID_40003:
							   // Узнаем текущее состояние пункта меню
							   if (dwEditState == MF_CHECKED)
								   EnableWindow(hButton1, FALSE);
							   else
								   EnableWindow(hButton1, TRUE);
							   // Изменим состояние пункта меню на противоположное, 
							   // т.е. если пункт меню был отмечен, то снимем отметку и наоборот
							   dwEditState ^= MF_CHECKED;
							   CheckMenuItem(hSubMenu2, ID_40003, MF_BYCOMMAND | dwButtonState);
							   break;
						   case ID_40004:
							   // Узнаем текущее состояние пункта меню
							   if (dwCheckboxState == MF_CHECKED)
								   EnableWindow(hEdit1, FALSE);
							   else
								   EnableWindow(hEdit1, TRUE);
							   // Изменим состояние пункта меню на противоположное, 
							   // т.е. если пункт меню был отмечен, то снимем отметку и наоборот
							   dwCheckboxState ^= MF_CHECKED;
							   CheckMenuItem(hSubMenu2, 1, MF_BYPOSITION | dwButtonState);
							   break;
						   case ID_40005:
							   // Узнаем текущее состояние пункта меню
							   if (dwButtonState == MF_CHECKED)
								   EnableWindow(hCheck1, FALSE);
							   else
								   EnableWindow(hCheck1, TRUE);
							   // Изменим состояние пункта меню на противоположное, 
							   // т.е. если пункт меню был отмечен, то снимем отметку и наоборот
							   dwButtonState ^= MF_CHECKED;
							   CheckMenuItem(hSubMenu2, ID_40005, MF_BYCOMMAND | dwButtonState);
							   break;


						   }

					   }
					   if (id >= 40006 && id <= 40008)
					   {
						   // Установим отметку на выбранном пункте в радио-группе элементов меню 
						   CheckMenuRadioItem(hSubMenu3, ID_40006, ID_40008, id, MF_BYCOMMAND);

						   switch (id)
						   {
						   case 40006:
							   EnableWindow(hButton2, TRUE);
							   EnableWindow(hEdit2, FALSE);
							   EnableWindow(hCheck2, FALSE);
							   break;
						   case 40007:
							   EnableWindow(hButton2, FALSE);
							   EnableWindow(hEdit2, TRUE);
							   EnableWindow(hCheck2, FALSE);
							   break;
						   case 40008:
							   EnableWindow(hButton2, FALSE);
							   EnableWindow(hEdit2, FALSE);
							   EnableWindow(hCheck2, TRUE);
							   break;


						   }
					   }
	}


		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
