#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <CommCtrl.h>

HWND hSpin, hEdit1,hEdit2;
TCHAR text[300];


BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int count;
	switch (message)
	{
	case WM_INITDIALOG:
	{
						  hSpin = GetDlgItem(hWnd, IDC_SPIN2);
						  hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
						  hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);

						  // ��������� �������� ��������
						  //SendDlgItemMessage(hWnd, IDC_SPIN1, UDM_SETRANGE, 0, 100);
						 SendMessage(hSpin, UDM_SETRANGE32,50,1000);

						  //������� ������� ����������
						  //UDACCEL pAcceleration[3] = { { 1, 20 }, { 3, 100 }, { 5, 500 } };
						  UDACCEL pAcceleration[] = {  1, 20  };
						  SendMessage(hSpin, UDM_SETACCEL,TRUE, LPARAM(pAcceleration));

						  // ��������� ��������
						  SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit2), 0);
						  SetWindowText(hEdit2, TEXT("50"));
						  SetWindowText(hEdit1, TEXT("������� ���������� Spin Control"));
	}
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			TCHAR str[100];
			// ������� ������� ������� ��������
			int nTime = SendMessage(hSpin, UDM_GETPOS32, 0, 0);
			SetTimer(hWnd, 1, nTime, NULL);
			// ������� ����� � Edit Control
			GetWindowText(hEdit1, text, 300);
			count = 1;
		}
		return TRUE;

	case WM_TIMER:
	{
					 TCHAR copytext[300] = { 0 };
					 if (count <= _tcslen(text)) //������ ���� �����?
					 {
						 //���, ����� ��������� � ��������� ���� ������
						 _tcsncpy_s(copytext,text,count++);
						 //������� ����� � ��������� �������� ����
						 SetWindowText(hWnd, copytext);
					 }
					 else
					 {
						 //��, ������� ������
						 KillTimer(hWnd, 1);
					 }
	}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}

