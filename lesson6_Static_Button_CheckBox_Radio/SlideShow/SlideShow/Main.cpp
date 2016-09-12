#include <Windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPTSTR  lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	// создаём главное окно приложения на основе модального диалога
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
};

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//дескрипторы двух кнопок и текущей подгружаемой картинки
	static HWND hStart, hStop, hPicture;
	//массив указателей на картинки
	static HBITMAP hBmp[5];



	switch (message)
	{
	case WM_INITDIALOG:
		//создаем кнопки и картинку
		hStart = CreateWindow(TEXT("Button"), TEXT("Start"), WS_CHILD | WS_VISIBLE, 20, 150, 50, 20, hWnd, NULL, NULL, 0);
		hStop = CreateWindow(TEXT("Button"), TEXT("Stop"), WS_CHILD | WS_VISIBLE, 100, 150, 50, 20, hWnd, NULL, NULL, 0);
		hPicture = CreateWindow(TEXT("Button"), 0, WS_CHILD | WS_VISIBLE|BS_BITMAP,50,20, 100, 100, hWnd, NULL, NULL, 0);
		//создаем массив указателей на ресурсы
		for (int i = 0; i < 5; i++)
			hBmp[i] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
		//устанавливаем картинку на кнопку
		SendMessage(hPicture, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));

		return TRUE;

	case WM_COMMAND:
	{
		//получаем дескриптор активного элемента
		HWND h = GetFocus();
		//строка для хранения текста
		TCHAR text[10];
		//получаем текст активного элемента
		GetWindowText(h, text, 10);
		//если текущий элемент кнопка Start
		if (!lstrcmp(text, TEXT("Start")))
		{
			//запускаем таймер
			SetTimer(hWnd, 1, 1000, NULL);
			//деактивируем кнопку Start
			EnableWindow(hStart, FALSE);
			//активируем кнопку Stop
			EnableWindow(hStop, TRUE);
			//переключаем фокус на кнопку Stop
			SetFocus(hStop);
		}
		else if (!lstrcmp(text, TEXT("Stop")))
		{
			//сброс таймера
			KillTimer(hWnd, 1);
			//деактивируем кнопку Stop и активируем кнопку Start
			EnableWindow(hStart, TRUE);
			EnableWindow(hStop, FALSE);
			//переключаем фокус на кнопку Start
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
			//устанавливаем картинку на кнопку
			SendMessage(hPicture, BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[index]));
	}
		return TRUE;


	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}