#include <Windows.h>
#include <tchar.h>
#include "resource.h"

//рписываем прототип диалоговой процедуры
BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//1- дескриптор окна
//2- сообщение
//3,4 - дополнительные парметры сообщения

//главная функция
INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hInstRrev, LPTSTR lcmdCommandLine, int cmdShow)
//1- дескриптор приложения
//2- дескритор приложения Win16(не используется. остался для совместимости)
//3- указатель на командную строку при запуске
//4- режим отображения окна (по умолчанию)
{
	//вызываем диалоговое окно
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	//1- дексриптор приложения
	//2- указатель на ресурс
	//3- дескриптор родительского окна
	//4- адрес диалоговой процедуры

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hStatic = CreateWindow(TEXT("Static"), TEXT("1234"), WS_CHILD | WS_VISIBLE, 486, 200, 70, 27, hWnd, NULL, NULL, 0);
	}
	return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd,0);
		return TRUE;


	}
	return FALSE;
}