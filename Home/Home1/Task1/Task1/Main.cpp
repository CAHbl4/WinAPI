#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <stdio.h>

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

struct TextProperties {
	int lengthLongest, lengthShortest, lengthAverage;
};

void CalcProperties(PVOID pvBuffer, TextProperties* res) {
	res->lengthLongest = 0;
	res->lengthShortest = 0;
	res->lengthAverage = 0;
	int i;
	
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hFile, hResult;
	static FILE* file;
	TCHAR str[256];
	PVOID TestText;

	switch (message)
	{
	case WM_INITDIALOG:
		hFile = GetDlgItem(hWnd, IDC_EDIT1);
		hResult = GetDlgItem(hWnd, IDC_EDIT2);
		SetWindowText(hFile, _T("test.txt"));
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			TCHAR fileName[256];
			GetWindowText(hFile, fileName, 256);
			if (lstrlen(fileName) == 0)
				MessageBox(hWnd, TEXT("Не введен путь к файлу"), TEXT("Error!!!"), MB_OK | MB_ICONERROR);
			else
			{
				if (!_wfopen_s(&file, fileName, _T("r"))) {
					
					fseek(file, 0L, SEEK_END);
					int sz = ftell(file);
					fseek(file, 0L, SEEK_SET);
					TestText = malloc(sz + 1);
					fread_s(TestText, sz + 1, 1, sz, file);
					((char *)TestText)[sz] = 0;
					fclose(file);

					if (IsTextUnicode(TestText, sz, NULL)){
						TextProperties res;
						CalcProperties(TestText, &res);
						_stprintf_s(str, _T("Самая длинная строка - %d\r\nСамая короткая строка - %d\r\nСредняя длинна строк - %d\r\n"), res.lengthLongest, res.lengthShortest, res.lengthAverage);
						SetWindowText(hResult, str);

					}

					else {
						MessageBox(hWnd, TEXT("Файл не в юникоде"), TEXT("Error!!!"), MB_OK | MB_ICONERROR);
					}

				}
				else {
					MessageBox(hWnd, TEXT("Ошибка открытия файла"), TEXT("Error!!!"), MB_OK | MB_ICONERROR);
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