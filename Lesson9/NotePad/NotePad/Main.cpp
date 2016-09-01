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
	static HMENU hMenu;
	static HWND hEdit;
	RECT rect;

	switch (message)
	{
	case WM_INITDIALOG:
		// Загрузим меню из ресурсов приложения
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		//отображаем меню
		SetMenu(hWnd, hMenu);
		//создаем EditControl;
		//получаем размеры клиентской области
		GetClientRect(hWnd, &rect);
		hEdit = CreateWindow(TEXT("Edit"), 0, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hWnd, 0, GetModuleHandle(NULL), 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//очистка Edit
		case ID_FILLE_NEW:
			SetWindowText(hEdit, 0);
			break;
			//выход
		case ID_FILLE_EXIT:
			EndDialog(hWnd, 0);
			break;
			//обработка команд редактирования
		case ID_EDIT_UNDO:
			// Отменим последнее действие
			SendMessage(hEdit, WM_UNDO, 0, 0);
			break;
		case ID_EDIT_CUT:
			// Удалим выделенный фрагмент текста в буфер обмена
			SendMessage(hEdit, WM_CUT, 0, 0);
			break;
		case ID_EDIT_COPY:
			// Скопируем выделенный фрагмент текста в буфер обмена
			SendMessage(hEdit, WM_COPY, 0, 0);
			break;
		case ID_EDIT_PASTE:
			// Вставим текст в Edit Control из буфера обмена
			SendMessage(hEdit, WM_PASTE, 0, 0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(hWnd,TEXT("Текстовый редактор\nВерсия 1.0.0\nРазработал ..."), TEXT("О программе"), MB_OK);
			break;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
