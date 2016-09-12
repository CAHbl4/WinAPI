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
	HMENU subFileMenu;
	HMENU subEditMenu;
	HMENU mainMenu;

	switch (message)
	{

	case WM_INITDIALOG:
		SetWindowText(hWnd, TEXT("Динамическое меню"));
		//создаем подменю File
		subFileMenu = CreatePopupMenu();
		//создаем пункты категории FILE
		AppendMenu(subFileMenu, MF_STRING, ID_FILE_NEW, TEXT("New"));
		AppendMenu(subFileMenu, MF_STRING, ID_FILE_OPEN, TEXT("Open"));
		AppendMenu(subFileMenu, MF_STRING, ID_FILE_SAVE, TEXT("Save"));
		AppendMenu(subFileMenu, MF_STRING, ID_FILE_SAVEAS, TEXT("Save as ..."));
		AppendMenu(subFileMenu, MF_STRING, ID_FILE_EXIT, TEXT("Exit"));
		//создаем подменю Edit
		subEditMenu = CreatePopupMenu();
		//создаем пункты категории FILE
		AppendMenu(subEditMenu, MF_STRING, ID_EDIT_UNDO, TEXT("Undo"));
		AppendMenu(subEditMenu, MF_STRING, ID_EDIT_CUT, TEXT("Cut"));
		AppendMenu(subEditMenu, MF_STRING, ID_EDIT_COPY, TEXT("Copy"));
		AppendMenu(subEditMenu, MF_STRING, ID_EDIT_PASTE, TEXT("Paste"));
		AppendMenu(subEditMenu, MF_STRING, ID_EDIT_FIND, TEXT("Find"));
		AppendMenu(subEditMenu, MF_STRING, ID_EDIT_REPLACE, TEXT("Replace"));

		//создаем главное меню
		mainMenu = CreateMenu();
		//добавлем категории и подменю
		AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subFileMenu, TEXT("File"));
		AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)subEditMenu, TEXT("Edit"));
		//подключаем меню
		SetMenu(hWnd, mainMenu);
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
