// Win32Project1.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;								// ������� ���������
TCHAR szTitle[MAX_LOADSTRING];					// ����� ������ ���������
TCHAR szWindowClass[MAX_LOADSTRING];			// ��� ������ �������� ����

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���������� ��� �����.
	MSG msg;
	HACCEL hAccelTable;

	// ������������� ���������� �����
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// ���� ��������� ���������:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW /*| CS_DBLCLKS*/;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND	- ��������� ���� ����������
//  WM_PAINT	-��������� ������� ����
//  WM_DESTROY	 - ������ ��������� � ������ � ���������.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR *text = _T("������"), str[100];
	//��� ������ �� ��������
	TEXTMETRIC tm;
	//������� ������� ����������
	RECT rect;
	SIZE size;

	//����������� ������� ����� ����
	UINT style = GetClassLong(hWnd, GCL_STYLE);
	SetClassLong(hWnd, GCL_STYLE, style | CS_DBLCLKS);


	switch (message)
	{
	//case WM_LBUTTONDOWN:
	//	MessageBox(hWnd, TEXT("������ ����� ������� ����"), TEXT("������ � �����"), MB_OK);
	//	break;
	case WM_RBUTTONUP:
		//MessageBox(hWnd, TEXT("���������� ������ ������ ����"), TEXT("������ � �����"), MB_OK);
		_stprintf_s(str, TEXT("���������� ���� x:%d, y:%d"), LOWORD(lParam), HIWORD(lParam));
		MessageBox(hWnd, str, TEXT("������ � �����"), MB_OK);
		break;
	case WM_LBUTTONDBLCLK:
		MessageBox(hWnd, TEXT("������� ������ ����"), TEXT("������ � �����"), MB_OK);
		break;
	case WM_RBUTTONDBLCLK:
		//��������� ������ ��������� ����
		SetWindowText(hWnd, TEXT("������� ������ ������ ������� ����"));
		break;
	case WM_MOUSEMOVE:
		_stprintf_s(str, TEXT("���������� ���� x:%d, y:%d"), LOWORD(lParam), HIWORD(lParam));
		SetWindowText(hWnd, str);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			MessageBox(hWnd, TEXT("����� � ����"), TEXT("����� � ���������"), MB_OK);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �������� ����� ��� ���������...
		SetBkColor(hdc, RGB(255,255,0)); // ������ ���
		SetTextColor(hdc, RGB(0, 0, 128)); // ����� �����
		TextOut(hdc, 200, 200, text, _tcsclen(text));//������� �����
		
		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
		GetTextMetrics(hdc, &tm);
		_stprintf_s(str, _T("tmHeight = %d\ntmInternalLeading =\%d\ntmExternalLeading = %d\ntmAscent = %d\ntmDescent = %d\n"), tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading, tm.tmAscent, tm.tmDescent);
		SetRect(&rect, 0, 20, 150, 100);
		DrawText(hdc, str, _tcslen(str), &rect, DT_LEFT);

		GetTextExtentPoint32(hdc, text, _tcsclen(text), &size);
		_stprintf_s(str, _T("������ ������ = %d\n������ ������ = %d"), size.cx, size.cy);
		SetRect(&rect, 50, 100, 150, 150);
		DrawText(hdc, str, _tcslen(str), &rect, DT_LEFT);



		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���������� ��������� ��� ���� "� ���������".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
