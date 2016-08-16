// Win32Project1.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Win32Project1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR *text = _T("Привет"), str[100];
	//для работы со шрифтами
	TEXTMETRIC tm;
	//рабочая область приложения
	RECT rect;
	SIZE size;

	//программное задание стиля окна
	UINT style = GetClassLong(hWnd, GCL_STYLE);
	SetClassLong(hWnd, GCL_STYLE, style | CS_DBLCLKS);


	switch (message)
	{
	//case WM_LBUTTONDOWN:
	//	MessageBox(hWnd, TEXT("Щелчок левой кнопкой мыши"), TEXT("Работа с мышью"), MB_OK);
	//	break;
	case WM_RBUTTONUP:
		//MessageBox(hWnd, TEXT("Отпускание правой кнопки мыши"), TEXT("Работа с мышью"), MB_OK);
		_stprintf_s(str, TEXT("Координаты мыши x:%d, y:%d"), LOWORD(lParam), HIWORD(lParam));
		MessageBox(hWnd, str, TEXT("Работа с мышью"), MB_OK);
		break;
	case WM_LBUTTONDBLCLK:
		MessageBox(hWnd, TEXT("Двойной щелчок мыши"), TEXT("Работа с мышью"), MB_OK);
		break;
	case WM_RBUTTONDBLCLK:
		//установка текста заголовка окна
		SetWindowText(hWnd, TEXT("Двойной щелчок правой кнопкой мыши"));
		break;
	case WM_MOUSEMOVE:
		_stprintf_s(str, TEXT("Координаты мыши x:%d, y:%d"), LOWORD(lParam), HIWORD(lParam));
		SetWindowText(hWnd, str);
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			MessageBox(hWnd, TEXT("Текст в окне"), TEXT("Текст в заголовке"), MB_OK);
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
		// TODO: добавьте любой код отрисовки...
		SetBkColor(hdc, RGB(255,255,0)); // Желтый фон
		SetTextColor(hdc, RGB(0, 0, 128)); // Синий шрифт
		TextOut(hdc, 200, 200, text, _tcsclen(text));//выводим текст
		
		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
		GetTextMetrics(hdc, &tm);
		_stprintf_s(str, _T("tmHeight = %d\ntmInternalLeading =\%d\ntmExternalLeading = %d\ntmAscent = %d\ntmDescent = %d\n"), tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading, tm.tmAscent, tm.tmDescent);
		SetRect(&rect, 0, 20, 150, 100);
		DrawText(hdc, str, _tcslen(str), &rect, DT_LEFT);

		GetTextExtentPoint32(hdc, text, _tcsclen(text), &size);
		_stprintf_s(str, _T("Ширина строки = %d\nВысота строки = %d"), size.cx, size.cy);
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

// Обработчик сообщений для окна "О программе".
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
