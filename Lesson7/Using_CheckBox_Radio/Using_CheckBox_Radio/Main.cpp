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
	static HWND hDialog, hRadio[3], hCheckBox[3], hButton,hStatic;
	RECT rect;
	GetClientRect(hWnd,&rect);
	int x=20, y=40,n=10;
	TCHAR str[20];

	switch (message)
	{
	case WM_INITDIALOG:
		//hDialog = GetDlgItem(hWnd, IDD_DIALOG1);
		SetWindowText(hWnd, TEXT("Покупка!!!"));

		for (int i = 0; i < 3; i++)
		{
			hCheckBox[i] = CreateWindow(TEXT("Button"), TEXT(""), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE, rect.left + x, rect.top + y, 150, 50, hWnd, 0, GetModuleHandle(0), 0);
			y = y + 50;
		}
		SetWindowText(hCheckBox[0], TEXT("Продукты"));
		SetWindowText(hCheckBox[1], TEXT("Напитки"));
		SetWindowText(hCheckBox[2], TEXT("Фрукты"));

		x = 220; y = 40;
		for (int i = 0; i < 3; i++)
		{
			hRadio[i] = CreateWindow(TEXT("Button"), 0, BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, rect.left + x, rect.top + y, 150, 50, hWnd, 0, 0, 0);
			wsprintf(str, TEXT("%d %c"), n,'%');
			n -= 5;
			SetWindowText(hRadio[i], str);
			y = y + 50;
		}
		hButton = CreateWindow(TEXT("Button"), TEXT("Расчитать!!!"), WS_CHILD | WS_VISIBLE, rect.left + 100, rect.top + 200, 100, 50, hWnd, 0, 0, 0);
		hStatic = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE, rect.left + 250, rect.top + 200, 100, 50, hWnd, 0, 0, 0);

		return TRUE;

	case WM_COMMAND:
	{
					   if (HWND(lParam) == hButton)
					   {

						   int Sum = 0;
						   for (int i = 0; i < 3; i++)
						   {
							   LRESULT lR = SendMessage(hCheckBox[i], BM_GETCHECK, 0, 0);
							   if (lR == BST_CHECKED )
								   if (i==0||i==1)
										Sum += 50;
								   else if (i==2)
										Sum += 20;
						   }
						   

						   int n = 0;
						   for (int i = 0; i < 3; i++)
						   {
							   LRESULT lR = SendMessage(hRadio[i], BM_GETCHECK, 0, 0);
							   if (lR == BST_CHECKED)
							   if (i == 0)
								   n= 10;
							   else if (i == 1)
								   n = 5;
							}

						   Sum = Sum - (Sum * n) / 100;
						   wsprintf(str, TEXT("Итого к оплате: %d"), Sum);
						   SetWindowText(hStatic, str);
					   }


	}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
