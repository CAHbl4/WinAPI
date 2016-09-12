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
						  // ��������� �������� ��������
						  SendMessage(hSpin, UDM_SETRANGE32, 0, 100);
						  // ��������� �������� ��� ��������
						  SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit), 0);
						  SetWindowText(hEdit, TEXT("0"));

						  // �������� ������ ���������
						  hStatus = CreateStatusWindow(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, 0, hWnd, ID_STATUS_BAR);

						  // �������� ������ ��������� �� ��������� ������
						  int parts[4] = { 40, 120, 240, -1 };
						  SendMessage(hStatus, SB_SETPARTS, 4, (LPARAM)parts);

						  // ��� ������ ������ ��������� ����� � ����������� ���������
						  SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)TEXT("�������: 0"));
						  SendMessage(hStatus, SB_SETTIPTEXT, 1, (LPARAM)TEXT("�������: 0"));
						  SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)TEXT("�������� 1: ����"));
						  SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM)TEXT("�������� 1: ����"));
						  SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)TEXT("�������� 2: ����"));
						  SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM)TEXT("�������� 2: ����"));

						  // �������� ������ �� ��������
						  hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));

						  // ��������� ������ � ������ ������ ������ ���������
						  SendMessage(hStatus, SB_SETICON, 0, (LPARAM)hIcon);

						  // ��������� ���� ���� ������ ���������
						  SendMessage(hStatus, SB_SETBKCOLOR, 0, (LPARAM)RGB(255, 200, 255));
	}
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_CHECK1)
		{
			LRESULT lResult = SendMessage(hCheck1, BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED)
			{
				SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)TEXT("�������� 1: ���"));
				SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM)TEXT("�������� 1: ���"));
			}
			else
			{
				SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)TEXT("�������� 1: ����"));
				SendMessage(hStatus, SB_SETTIPTEXT, 2, (LPARAM)TEXT("�������� 1: ����"));
			}
		}
		if (LOWORD(wParam) == IDC_CHECK2)
		{
			LRESULT lResult = SendMessage(hCheck2, BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED)
			{
				SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)TEXT("�������� 2: ���"));
				SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM)TEXT("�������� 2: ���"));
			}
			else
			{
				SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)TEXT("�������� 2: ����"));
				SendMessage(hStatus, SB_SETTIPTEXT, 3, (LPARAM)TEXT("�������� 2: ����"));
			}
		}
		return TRUE;
	case WM_VSCROLL:
		{
					   // ���������� ��������� ������� �� ���� �� ������� ��������
					   int pos;
					   TCHAR buf[30];
					   pos = SendMessage(hSpin, UDM_GETPOS, 0, 0);
					   wsprintf(buf, TEXT("�������: %d"), pos);
					   // ��������� ��������� �������� � ������ ���������
					   SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)buf);
					   SendMessage(hStatus, SB_SETTIPTEXT, 1, (LPARAM)buf);

		}
		return TRUE;
	}
	return FALSE;
}
