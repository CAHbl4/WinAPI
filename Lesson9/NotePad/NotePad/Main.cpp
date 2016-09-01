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
	static HMENU hMenu;
	static HWND hEdit;
	RECT rect;

	switch (message)
	{
	case WM_INITDIALOG:
		// �������� ���� �� �������� ����������
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		//���������� ����
		SetMenu(hWnd, hMenu);
		//������� EditControl;
		//�������� ������� ���������� �������
		GetClientRect(hWnd, &rect);
		hEdit = CreateWindow(TEXT("Edit"), 0, WS_CHILD | WS_VISIBLE | ES_WANTRETURN | ES_MULTILINE | ES_AUTOVSCROLL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hWnd, 0, GetModuleHandle(NULL), 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//������� Edit
		case ID_FILLE_NEW:
			SetWindowText(hEdit, 0);
			break;
			//�����
		case ID_FILLE_EXIT:
			EndDialog(hWnd, 0);
			break;
			//��������� ������ ��������������
		case ID_EDIT_UNDO:
			// ������� ��������� ��������
			SendMessage(hEdit, WM_UNDO, 0, 0);
			break;
		case ID_EDIT_CUT:
			// ������ ���������� �������� ������ � ����� ������
			SendMessage(hEdit, WM_CUT, 0, 0);
			break;
		case ID_EDIT_COPY:
			// ��������� ���������� �������� ������ � ����� ������
			SendMessage(hEdit, WM_COPY, 0, 0);
			break;
		case ID_EDIT_PASTE:
			// ������� ����� � Edit Control �� ������ ������
			SendMessage(hEdit, WM_PASTE, 0, 0);
			break;
		case ID_HELP_ABOUT:
			MessageBox(hWnd,TEXT("��������� ��������\n������ 1.0.0\n���������� ..."), TEXT("� ���������"), MB_OK);
			break;
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
