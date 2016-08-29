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
	static HWND hRadio1, hRadio2, hRadio3, hRadio4, hRadio5, hRadio6, hButton;
	switch (message)
	{
	case WM_INITDIALOG:
		//�������� �����������
		hRadio1 = GetDlgItem(hWnd, IDC_RADIO1);
		hRadio2 = GetDlgItem(hWnd, IDC_RADIO2);
		hRadio3 = GetDlgItem(hWnd, IDC_RADIO3);
		hRadio4 = GetDlgItem(hWnd, IDC_RADIO4);
		hRadio5 = GetDlgItem(hWnd, IDC_RADIO5);
		hRadio6 = GetDlgItem(hWnd, IDC_RADIO6);
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		//�������� ������ Radio2 � Radio6 �������� ���������
		SendMessage(hRadio2, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		SendMessage(hRadio6, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
		return TRUE;
	case WM_COMMAND:
		//������������ ������ ������
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			LRESULT lR;
			//�������� 1 ������
			lR = SendMessage(hRadio1, BM_GETCHECK, 0, 0);
			if (lR == BST_CHECKED)
				MessageBox(hWnd,TEXT("������� ������ 1"), TEXT("������ � �������������"),MB_OK);
			else
			{
				lR = SendMessage(hRadio2, BM_GETCHECK, 0, 0);
				if (lR == BST_CHECKED)
					MessageBox(hWnd, TEXT("������� ������ 2"), TEXT("������ � �������������"), MB_OK);
				else
				{
					lR = SendMessage(hRadio3, BM_GETCHECK, 0, 0);
					if (lR == BST_CHECKED)
						MessageBox(hWnd, TEXT("������� ������ 3"), TEXT("������ � �������������"), MB_OK);
				}
			}
			//�������� 2 ������
			lR = SendMessage(hRadio4, BM_GETCHECK, 0, 0);
			if (lR == BST_CHECKED)
				MessageBox(hWnd, TEXT("������� ������ 4"), TEXT("������ � �������������"), MB_OK);
			else
			{
				lR = SendMessage(hRadio5, BM_GETCHECK, 0, 0);
				if (lR == BST_CHECKED)
					MessageBox(hWnd, TEXT("������� ������ 5"), TEXT("������ � �������������"), MB_OK);
				else
				{
					lR = SendMessage(hRadio6, BM_GETCHECK, 0, 0);
					if (lR == BST_CHECKED)
						MessageBox(hWnd, TEXT("������� ������ 6"), TEXT("������ � �������������"), MB_OK);
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
