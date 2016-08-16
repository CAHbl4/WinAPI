#include <windows.h>
#include <tchar.h>

//�������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
//HWND - ���������� ����
//UINT - ��� ���������
//WPARAM, LPARAM - �������������� ��������� ���������

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
//HINSTANSE - ���������� ����������
//������ �������� ���������� ����������
//������ �������� �������� ������ ��� ������������� � ������� �������� windows
//LPTSTR lpszCmdLine - ��������� �� ��������� ������, ������� ����������� ���������
//int nCmdShow - ����� ����������� ����
{
	//�������� ������ WinMain
	//1 - ���������� ��������� ����
	//2 - ������� ������ ���� ��������� � ���������������� � windows
	//3 - ���������� ����
	//4 - ������������ ���� ��������� ���������, �� ������� ��������� � ������� ���������
	//5 - ��������� ������ ���������

	//������ ���������� ����������

	HWND hWnd; //���������� ����
	MSG Msg; //��������� message
	WNDCLASSEX wcl; //��������� ����
	wchar_t szClassName[] = L"������ ���������� Win32"; //��� ������ ����

	//1
	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX
	// ������������ �� ����, ���� ������ ������ �� ����������� ��� �� ���������
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - ����� ������ ����
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ �������	
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ���������� ���� ����� ������
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassName;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

	//2
	//������������ � �������
	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	// ������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassName,	//��� ������ ����
		TEXT("Windows ����������"), // ��������� ����
		WS_OVERLAPPEDWINDOW,				// ����� ����
		/* ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����  */
		//CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		//CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		//CW_USEDEFAULT,	// ������ ����
		//CW_USEDEFAULT,	// ������ ����
		100,100,300,200,
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������

	//3
	ShowWindow(hWnd, nCmdShow); //����������� ����
	UpdateWindow(hWnd); // ����������� ����

	//4
	while (GetMessage(&Msg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ���������
	{
		TranslateMessage(&Msg);	// ���������� ���������
		DispatchMessage(&Msg);	// ��������������� ���������
	}
	return Msg.wParam;
}
//������� ���������
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hDC; //���������� ����������
	PAINTSTRUCT ps; //��������� ��� ���������� ������� ������� 
	RECT rect; //���� ������� �������

	switch (uMessage)
	{
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			DrawText(hDC, L"���� ������!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
		break;
		case WM_DESTROY: // ��������� � ���������� ���������
			PostQuitMessage(0); // ������� ��������� WM_QUIT
		break;
		default:
			// ��� ���������, ������� �� �������������� � ������ ������� ������� 
			// ������������ ������� Windows �� ��������� �� ���������
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}


