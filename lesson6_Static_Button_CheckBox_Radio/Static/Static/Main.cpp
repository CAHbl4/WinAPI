#include <Windows.h>
#include <tchar.h>
#include "resource.h"

//��������� �������� ���������� ���������
BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//1- ���������� ����
//2- ���������
//3,4 - �������������� �������� ���������

//������� �������
INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hInstRrev, LPTSTR lcmdCommandLine, int cmdShow)
//1- ���������� ����������
//2- ��������� ���������� Win16(�� ������������. ������� ��� �������������)
//3- ��������� �� ��������� ������ ��� �������
//4- ����� ����������� ���� (�� ���������)
{
	//�������� ���������� ����
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	//1- ���������� ����������
	//2- ��������� �� ������
	//3- ���������� ������������� ����
	//4- ����� ���������� ���������

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hStatic = CreateWindow(TEXT("Static"), TEXT("1234"), WS_CHILD | WS_VISIBLE, 486, 200, 70, 27, hWnd, NULL, NULL, 0);
	}
	return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd,0);
		return TRUE;


	}
	return FALSE;
}