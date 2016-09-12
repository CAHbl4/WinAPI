#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include<CommCtrl.h>

const int MIN=0;
const int MAX=400;

HWND hSliderH, hSliderV;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hSliderH = GetDlgItem(hWnd, IDC_SLIDER1);
		hSliderV = GetDlgItem(hWnd, IDC_SLIDER2);
		SendMessage(hSliderH, TBM_SETRANGE, TRUE, MAKELPARAM(MIN, MAX));
		SendMessage(hSliderV, TBM_SETRANGE, TRUE, MAKELPARAM(MIN, MAX));
		return TRUE;
	case WM_VSCROLL:
	{
					   static int nOldPosition = 0;
					   int nCurrrentPosition = SendMessage(hSliderV, TBM_GETPOS, TRUE, MAKELPARAM(MIN, MAX));
					   RECT rect;
					   GetWindowRect(hWnd, &rect);
					   switch (LOWORD(wParam))
					   {
					   case TB_BOTTOM:
						   // ������ ������� �End� (VK_END) � ��������  ��������������� � ������� ������ ���������
						   rect.bottom += MAX - nOldPosition;
						   break;
					   case TB_TOP:
						   // ������ ������� �Home� (VK_HOME) � �������� ��������������� � ������� ������� ���������
						   rect.bottom -= nOldPosition - MIN;
						   break;
					   case TB_LINEUP:
						   // ������ ������� �������� ������ (VK_UP) 
						   if (nCurrrentPosition > MIN) rect.bottom--;
						   break;
					   case TB_LINEDOWN:
						   // ������ ������� �������� ���� (VK_DOWN) 
						   if (nCurrrentPosition < MAX) rect.bottom++;
						   break;
					   case TB_PAGEDOWN:
					   case TB_PAGEUP:
					   case TB_THUMBPOSITION:
						   // �������� ������ ���� ����� ����������� �������� 
					   case TB_THUMBTRACK:
						   // �������� ������������ � ������� ����
						   rect.bottom += nCurrrentPosition - nOldPosition;
						   break;
					   }
					   nOldPosition = nCurrrentPosition;
					   MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 1);
	}
		return TRUE;

	case WM_HSCROLL:
	{
					   static int nOldPosition = 0;
					   int nCurrrentPosition = SendMessage(hSliderH, TBM_GETPOS, TRUE, MAKELPARAM(MIN, MAX));
					   RECT rect;
					   GetWindowRect(hWnd, &rect);
					   switch (LOWORD(wParam))
					   {
					   case TB_BOTTOM:
						   // ������ ������� �End� (VK_END) � ��������  ��������������� � ������� ������ ���������
						   rect.right += MAX - nOldPosition;
						   break;
					   case TB_TOP:
						   // ������ ������� �Home� (VK_HOME) � �������� ��������������� � ������� ������� ���������
						   rect.right -= nOldPosition - MIN;
						   break;
					   case TB_LINEUP:
						   // ������ ������� �������� ������ (VK_UP) 
						   if (nCurrrentPosition > MIN) rect.right--;
						   break;
					   case TB_LINEDOWN:
						   // ������ ������� �������� ���� (VK_DOWN) 
						   if (nCurrrentPosition < MAX) rect.right++;
						   break;
					   case TB_PAGEDOWN:
					   case TB_PAGEUP:
					   case TB_THUMBPOSITION:
						   // �������� ������ ���� ����� ����������� �������� 
					   case TB_THUMBTRACK:
						   // �������� ������������ � ������� ����
						   rect.right += nCurrrentPosition - nOldPosition;
						   break;
					   }
					   nOldPosition = nCurrrentPosition;
					   MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 1);
	}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}


