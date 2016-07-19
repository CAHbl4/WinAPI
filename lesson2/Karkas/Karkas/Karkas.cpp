#include <windows.h>
#include <tchar.h>

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
//HWND - дескриптор окна
//UINT - код сообщения
//WPARAM, LPARAM - дополнительные параметры сообщения

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
//HINSTANSE - дескриптор приложения
//первый параметр дескриптор приложения
//второй параметр оставлен только для совместимости с ранними версиями windows
//LPTSTR lpszCmdLine - указатель на командную строку, которой запускалась программа
//int nCmdShow - режим отображения окна
{
	//алгоритм работы WinMain
	//1 - определить структуру окна
	//2 - создать объект этой структуры и зарегистрировать в windows
	//3 - отобразить окно
	//4 - организовать цикл просмотра сообщений, те которые поступили в очередь сообщения
	//5 - закончить работу программу

	//задаем глобальные переменные

	HWND hWnd; //дескриптор окна
	MSG Msg; //структура message
	WNDCLASSEX wcl; //структура окна
	wchar_t szClassName[] = L"Первое приложение Win32"; //имя класса окна

	//1
	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX
	// Перерисовать всё окно, если изменён размер по горизонтали или по вертикали
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - стиль класса окна
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// загрузка стандартного курсора	
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// заполнение окна белым цветом
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassName;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна

	//2
	//регистрируем в системе
	if (!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход

	// создаем окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassName,	//имя класса окна
		TEXT("Windows приложения"), // заголовок окна
		WS_OVERLAPPEDWINDOW,				// стиль окна
		/* Заголовок, рамка, позволяющая менять размеры, системное меню, кнопки развёртывания и свёртывания окна  */
		//CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		//CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		//CW_USEDEFAULT,	// ширина окна
		//CW_USEDEFAULT,	// высота окна
		100,100,300,200,
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения

	//3
	ShowWindow(hWnd, nCmdShow); //отображение окна
	UpdateWindow(hWnd); // перерисовка окна

	//4
	while (GetMessage(&Msg, NULL, 0, 0)) // получение очередного сообщения из очереди сообщений
	{
		TranslateMessage(&Msg);	// трансляция сообщения
		DispatchMessage(&Msg);	// диспетчеризация сообщений
	}
	return Msg.wParam;
}
//оконная процедура
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hDC; //дескриптор устройства
	PAINTSTRUCT ps; //структура для прорисовки рабочей области 
	RECT rect; //сама рабочая область

	switch (uMessage)
	{
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			DrawText(hDC, L"Всем привет!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
		break;
		case WM_DESTROY: // сообщение о завершении программы
			PostQuitMessage(0); // посылка сообщения WM_QUIT
		break;
		default:
			// все сообщения, которые не обрабатываются в данной оконной функции 
			// направляются обратно Windows на обработку по умолчанию
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}


