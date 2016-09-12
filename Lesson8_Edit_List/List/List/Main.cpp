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
	static HWND hList1, hList2, hEditAdd, hEditFind, hButtonAdd, hButtonFind, hButtonDelete, hButtonClear, hButton5;
	int index;
	switch (message)
	{
	case WM_INITDIALOG:
		//��������� ������������
		hList1 = GetDlgItem(hWnd, IDC_LIST1);
		hList2 = GetDlgItem(hWnd, IDC_LIST2);
		hEditAdd = GetDlgItem(hWnd, IDC_EDIT1);
		hEditFind = GetDlgItem(hWnd, IDC_EDIT2);
		hButtonAdd = GetDlgItem(hWnd, IDC_BUTTON1);
		hButtonFind = GetDlgItem(hWnd, IDC_BUTTON2);
		hButtonDelete = GetDlgItem(hWnd, IDC_BUTTON3);
		hButtonClear = GetDlgItem(hWnd, IDC_BUTTON4);

		//������������ ������
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("����"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("�� ������"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("��������"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("�����"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
		SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)TEXT("�����"));

		//������������ ������ � ������������� �������
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("�����"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("�����"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("����"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("�� ������"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("���������"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("�������"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("������"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("�������"));
		SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)TEXT("���������"));
		
		return TRUE;


		//��������� ������� ������
	case WM_COMMAND:
	{
					   TCHAR str[100];
					   switch (LOWORD(wParam))
					   {
					   case IDC_BUTTON1:
						   //��������� �������� �����
						   GetWindowText(hEditAdd, str, 100);
						   //��������� � ������
						   SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)str);
						   break;
					   case IDC_BUTTON4:
						   //������� ������
						   SendMessage(hList1, LB_RESETCONTENT, 0, 0);
						   break;
					   case IDC_BUTTON2:
					   {//�������� �� ������
										   //�������� ������ ����������� ��������
										   index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
										   //���� ��� ������ ������
										   if (index != LB_ERR)
											   //�������
											   SendMessage(hList1, LB_DELETESTRING, (WPARAM)index, 0);
					   }
						   break;
					   case IDC_BUTTON3:
						   //����� ��������
						   //��������� �������� ����� �� Edit2
						   GetWindowText(hEditFind, str, 100);
						   //����� � ����������
						   index = SendMessage(hList1, LB_SELECTSTRING, 0, (LPARAM)str);
						   if (index == LB_ERR)
							   MessageBox(hWnd, TEXT("������ ����� ��� � ������"), 0, MB_OK | MB_ICONERROR);
						   break;
					   case IDC_BUTTON5:
					   {
										   //���������� ���������� ���������� ���������
										   int count = SendMessage(hList2, LB_GETSELCOUNT, 0, 0);
										   // ������� ������ ������������ ������� ��� �������� �������� ��������� ��������� ������
										   int *p = new int[count];
										   // �������� ������������ ������ ��������� ���������� ��������� ������ 
										   SendMessage(hList2, LB_GETSELITEMS, count, LPARAM(p));
										   //������� ������� ��������� ���������
										   for (int i = 0; i < count; i++)
										   {
											   //�������� �������� ��������
											   SendMessage(hList2, LB_GETTEXT, (WPARAM)p[i], (LPARAM)str);
											   MessageBox(hWnd, str, TEXT("������������� �����"), MB_OK | MB_ICONINFORMATION);
										   }

										   delete[] p;
					   }
						   break;
					   }
	}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
