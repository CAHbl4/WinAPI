#include <Windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
	LPTSTR lpszCmdLine, int nCmdShow)
{
	//�������� MessageBox
	if (MessageBox(NULL, TEXT("������ ������ ��� ���?"), TEXT("��������!!!"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
		// �������� ��������� ������
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	else
	MessageBox(NULL, TEXT("����!!!"), TEXT("�� ���� �� ������, ��� �!!!"), MB_OK);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		if (wParam==IDC_BUTTON1)
		EndDialog(hWnd, 0); // ��������� ��������� ������
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0); // ��������� ��������� ������
		return TRUE;
	}
	return FALSE;
}


