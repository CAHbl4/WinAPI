#include <Windows.h>
#include <tchar.h>
#include "resource1.h"

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
