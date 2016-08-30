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
	static HWND hLogin, hPassword,hEdit, hButton;

	switch (message)
	{
	case WM_INITDIALOG:
		hLogin = GetDlgItem(hWnd, IDC_EDIT1);
		hPassword = GetDlgItem(hWnd, IDC_EDIT2);
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT3);

		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			TCHAR login[20], passwd[20],rez[100];
			GetWindowText(hLogin, login, 20);
			GetWindowText(hPassword, passwd, 20);
			if (lstrlen(login) == 0 || lstrlen(passwd) == 0)
				MessageBox(hWnd, TEXT("Не заполнены поля формы"), TEXT("Error!!!"), MB_OK | MB_ICONERROR);
			else
			{
				wsprintf(rez, TEXT("Login: %s\r\nPassword: %s"), login, passwd);

				MessageBox(hWnd, rez, TEXT("Авторизация"), MB_OK | MB_ICONERROR);
				SetWindowText(hEdit, rez);

			}

		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
