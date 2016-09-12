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
	//����������� ��������� ����������
	static HWND hButton1, hButton2, hEdit1, hEdit2, hCheck1, hCheck2;
	//����������� ����
	static HMENU  hMenu, hSubMenu, hSubMenu2, hSubMenu3;
	//��� ��������� ��������� ����������
	static DWORD dwButtonState = MF_CHECKED, dwEditState = MF_CHECKED, dwCheckboxState=MF_CHECKED;
	
	switch (message)
	{
	case WM_INITDIALOG:
		//�������� ����������� ��������� ����������
		hButton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit1 = GetDlgItem(hWnd, IDC_EDIT1);
		hCheck1 = GetDlgItem(hWnd, IDC_CHECK1);

		hButton2 = GetDlgItem(hWnd, IDC_BUTTON2);
		hEdit2 = GetDlgItem(hWnd, IDC_EDIT2);
		hCheck2 = GetDlgItem(hWnd, IDC_CHECK2);

		// �������� ���� �� �������� ����������
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		//��������� �������
		hSubMenu = GetSubMenu(hMenu, 0);
		hSubMenu2 = GetSubMenu(hSubMenu, 0);
		hSubMenu3 = GetSubMenu(hSubMenu, 1);
		
		//������������� ������ � CheckBox
		SendMessage(hCheck1, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
		SendMessage(hCheck2, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);

		//������������� ��������� ����� � ������2 ����
		//1- ���������� �������
		//2- ��������� ������ ��������, ��������� � ������
		//3- �������� ������ ��������
		//4- ������ ��������, ������� ����� �������
		CheckMenuRadioItem(hSubMenu3, 0, 2, 1, MF_BYPOSITION);
		return TRUE;

	//��������� ��� ������ ����������� ����
	case WM_CONTEXTMENU:
		//1- ���������� �������
		//2- ������������
		//3- ���������� x
		//4- ���������� y
		//5- �������� 0
		//6- ���������� ����
		//7- �� ������������
		TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);

		return TRUE;

		//��������� ��������� �� ��������� ����������
	case WM_COMMAND:
	{
					   int id = LOWORD(wParam);
					   //������� ��������� � ������ ������ ����
					   if (id >= ID_40003&&id <= ID_40005)
					   {
						   switch (id)
						   {
							   //������ ����� ����
						   case ID_40003:
							   // ������ ������� ��������� ������ ����
							   if (dwEditState == MF_CHECKED)
								   EnableWindow(hButton1, FALSE);
							   else
								   EnableWindow(hButton1, TRUE);
							   // ������� ��������� ������ ���� �� ���������������, 
							   // �.�. ���� ����� ���� ��� �������, �� ������ ������� � ��������
							   dwEditState ^= MF_CHECKED;
							   CheckMenuItem(hSubMenu2, ID_40003, MF_BYCOMMAND | dwButtonState);
							   break;
						   case ID_40004:
							   // ������ ������� ��������� ������ ����
							   if (dwCheckboxState == MF_CHECKED)
								   EnableWindow(hEdit1, FALSE);
							   else
								   EnableWindow(hEdit1, TRUE);
							   // ������� ��������� ������ ���� �� ���������������, 
							   // �.�. ���� ����� ���� ��� �������, �� ������ ������� � ��������
							   dwCheckboxState ^= MF_CHECKED;
							   CheckMenuItem(hSubMenu2, 1, MF_BYPOSITION | dwButtonState);
							   break;
						   case ID_40005:
							   // ������ ������� ��������� ������ ����
							   if (dwButtonState == MF_CHECKED)
								   EnableWindow(hCheck1, FALSE);
							   else
								   EnableWindow(hCheck1, TRUE);
							   // ������� ��������� ������ ���� �� ���������������, 
							   // �.�. ���� ����� ���� ��� �������, �� ������ ������� � ��������
							   dwButtonState ^= MF_CHECKED;
							   CheckMenuItem(hSubMenu2, ID_40005, MF_BYCOMMAND | dwButtonState);
							   break;


						   }

					   }
					   if (id >= 40006 && id <= 40008)
					   {
						   // ��������� ������� �� ��������� ������ � �����-������ ��������� ���� 
						   CheckMenuRadioItem(hSubMenu3, ID_40006, ID_40008, id, MF_BYCOMMAND);

						   switch (id)
						   {
						   case 40006:
							   EnableWindow(hButton2, TRUE);
							   EnableWindow(hEdit2, FALSE);
							   EnableWindow(hCheck2, FALSE);
							   break;
						   case 40007:
							   EnableWindow(hButton2, FALSE);
							   EnableWindow(hEdit2, TRUE);
							   EnableWindow(hCheck2, FALSE);
							   break;
						   case 40008:
							   EnableWindow(hButton2, FALSE);
							   EnableWindow(hEdit2, FALSE);
							   EnableWindow(hCheck2, TRUE);
							   break;


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
