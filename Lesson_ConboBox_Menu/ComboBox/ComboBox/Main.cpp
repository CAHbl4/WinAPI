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

		//������� �������� ������
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("����"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("�����"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("����"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("�����"));
		return TRUE;
	case WM_COMMAND:
		//��������� ��� ������ �������� �� ������������� ������
		if (LOWORD(wParam) == IDC_COMBO1 && HIWORD(wParam) == CBN_SELCHANGE)
		{
			// ������� ������ ���������� �������� ComboBox
			int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			//������� ������ �������
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			switch (index)
			{
			case 0:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("�������"));
				SendMessage(hList, LB_SETITEMDATA, 0, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
				SendMessage(hList, LB_SETITEMDATA, 1, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("�������"));
				SendMessage(hList, LB_SETITEMDATA, 2, 28);
				break;
			case 1:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("����"));
				SendMessage(hList, LB_SETITEMDATA, 0, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
				SendMessage(hList, LB_SETITEMDATA, 1, 30);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("���"));
				SendMessage(hList, LB_SETITEMDATA, 2, 31);
				break;
			case 2:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("����"));
				SendMessage(hList, LB_SETITEMDATA, 0, 30);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("����"));
				SendMessage(hList, LB_SETITEMDATA, 1, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
				SendMessage(hList, LB_SETITEMDATA, 2, 31);
				break; 
			case 3:
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("��������"));
				SendMessage(hList, LB_SETITEMDATA, 0, 30);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("�������"));
				SendMessage(hList, LB_SETITEMDATA, 1, 31);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
				SendMessage(hList, LB_SETITEMDATA, 2, 30);
				break;
			}
		}
		if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE)
		{
			// ������� ������ ���������� �������� ListBox
			int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			TCHAR str[20];
			// �������� ���������� ����
			int day=SendMessage(hList, LB_GETITEMDATA, index, 0);
			// ������ ����� � ���������� �������� ������
			SendMessage(hList, LB_GETTEXT, index, LPARAM(str));
			if (!lstrcmp(str, TEXT("�������")))
			{	// ���������, ���������� ��� ��� ���
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

