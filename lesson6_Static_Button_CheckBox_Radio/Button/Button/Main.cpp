#include <Windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPTSTR  lpszCmdLine, int nCmdShow)
{
	// ������ ������� ���� ���������� �� ������ ���������� �������
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
};

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1,hButton2,hButton3,hStatic;
	switch (message)
	{
	case WM_INITDIALOG:
		//�������� ������
		hButton3 = CreateWindow(TEXT("Button"), TEXT("Programm Button"), WS_CHILD | WS_VISIBLE, 20, 100, 150, 50, hWnd, NULL, NULL, 0);
		//�������� �������
		hStatic = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE, 200, 100, 150, 50, hWnd, NULL, NULL, 0);
		//��������� ������������ ������ �� ��������������
		hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hButton2 = GetDlgItem(hWnd, IDC_BUTTON2);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			MessageBox(hWnd, TEXT("������ ������ ������!!!"), TEXT("������ � ��������"), MB_OK);
			//��������� ������ � ������ 3
			SetWindowText(hButton3, TEXT("����� ����!!!"));
		}
		else if (LOWORD(wParam) == IDC_BUTTON2)
			MessageBox(hWnd, TEXT("������ ������ ������!!!"), TEXT("������ � ��������"), MB_OK);
		else if ((HWND)lParam == hButton3)
			SetWindowText(hStatic, TEXT("�� ������ ������ 3"));

		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}