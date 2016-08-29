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
		//��������� ������������ � ������ �������� ����������� ����
	case WM_INITDIALOG:
		hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hStart = GetDlgItem(hWnd, IDC_BUTTON2);
		hCheckBox = GetDlgItem(hWnd, IDC_CHECK1);
		//������������� ���������� ������ �������� ��������� BM_SETCHECK
		SendMessage(hCheckBox, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		return TRUE;
	case WM_COMMAND:
		//���� ������ ������ start(stop)
		if (LOWORD(wParam) == IDC_BUTTON2)
		{
			TCHAR str[10];
			//�������� ������� ������
			GetWindowText(hStart, str, 10);
			//���������, ��� ��������
			if (!lstrcmp(str, TEXT("Start")))
			{
				SetWindowText(hStart, TEXT("Stop"));
				//��������� ������
				SetTimer(hWnd, 1, 1000, NULL);

			}
			else
			{
				SetWindowText(hStart, TEXT("Start"));
				KillTimer(hWnd, 1);
			}

		}
		return TRUE;
		//��������� ��������� �� �������
	case WM_TIMER:
	{
		static time_t t;
		static TCHAR str[100];
		t = time(NULL);
		// �������� ��������� ����� � ��������� 
		struct tm DateTime;
		localtime_s(&DateTime,&t);
		//��������� ���������� �� CheckBox
		LRESULT lResult = SendMessage(hCheckBox, BM_GETCHECK, 0, 0);
		//���� ���� ����������
		if (lResult==BST_CHECKED)
			//��������� ������ � ������������ ������
			_tcsftime(str, 100, TEXT("%H:%M:%S  %d.%m.%Y  %A"), &DateTime);
		else
			//��������� ������ ��� ����������� ������
			_tcsftime(str, 100, TEXT("%H:%M  %d.%m.%Y  %A"), &DateTime);
		//������� ������ � Button1
		SetWindowText(hButton1, str);
	}
		return TRUE;


	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}


	return FALSE;
}
