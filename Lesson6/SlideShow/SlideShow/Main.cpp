#include <Windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPTSTR  lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	// ������ ������� ���� ���������� �� ������ ���������� �������
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
};

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//����������� ���� ������ � ������� ������������ ��������
	static HWND hStart, hStop, hPicture;
	//������ ���������� �� ��������
	static HBITMAP hBmp[5];



	switch (message)
	{
	case WM_INITDIALOG:
		//������� ������ � ��������
		hStart = CreateWindow(TEXT("Button"), TEXT("Start"), WS_CHILD | WS_VISIBLE, 20, 150, 50, 20, hWnd, NULL, NULL, 0);
		hStop = CreateWindow(TEXT("Button"), TEXT("Stop"), WS_CHILD | WS_VISIBLE, 100, 150, 50, 20, hWnd, NULL, NULL, 0);
		hPicture = CreateWindow(TEXT("Button"), 0, WS_CHILD | WS_VISIBLE|BS_BITMAP,50,20, 100, 100, hWnd, NULL, NULL, 0);
		//������� ������ ���������� �� �������
		for (int i = 0; i < 5; i++)
			hBmp[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		//������������� �������� �� ������
		SendMessage(hPicture, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));

		return TRUE;

	case WM_COMMAND:
	{
		//�������� ���������� ��������� ��������
		HWND h = GetFocus();
		//������ ��� �������� ������
		TCHAR text[10];
		//�������� ����� ��������� ��������
		GetWindowText(h, text, 10);
		//���� ������� ������� ������ Start
		if (!lstrcmp(text, TEXT("Start")))
		{
			//��������� ������
			SetTimer(hWnd, 1, 1000, NULL);
			//������������ ������ Start
			EnableWindow(hStart, FALSE);
			//���������� ������ Stop
			EnableWindow(hStop, TRUE);
			//����������� ����� �� ������ Stop
			SetFocus(hStop);
		}
		else if (!lstrcmp(text, TEXT("Stop")))
		{
			//����� �������
			KillTimer(hWnd, 1);
			//������������ ������ Stop � ���������� ������ Start
			EnableWindow(hStart, TRUE);
			EnableWindow(hStop, FALSE);
			//����������� ����� �� ������ Start
			SetFocus(hStart);
		}
	}
		return TRUE;
	case WM_TIMER:
	{
			static int index = 0;
			index++;
			if (index > 4)
				 index = 0;
			//������������� �������� �� ������
			SendMessage(hPicture, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[index]));
	}
		return TRUE;


	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}