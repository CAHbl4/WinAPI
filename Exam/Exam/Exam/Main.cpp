#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <fstream>
#include<vector>
using namespace std;

std::vector<int> numbers;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK CreateDlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hi;
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow) {
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HMENU hMenu;
	wifstream in;
	static HWND hDialog, hEdit, hList, hCheckBox1, hCheckBox2;
	switch (message) {

	case WM_INITDIALOG:
		hDialog = hWnd;
		hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
		hCheckBox1 = GetDlgItem(hWnd, IDC_CHECK1);
		hCheckBox2 = GetDlgItem(hWnd, IDC_CHECK2);
		SetMenu(hWnd, hMenu);
		return TRUE;
	case WM_COMMAND:

		switch (LOWORD(wParam)) {
		case ID_FILE_OPEN:
			{
				TCHAR FullPath[MAX_PATH] = {0};
				OPENFILENAME open = {sizeof(OPENFILENAME)};
				open.hwndOwner = hWnd;
				open.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0");
				open.lpstrFile = FullPath;
				open.nMaxFile = MAX_PATH;
				open.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
				open.lpstrDefExt = TEXT("txt");
				if (GetOpenFileName(&open)) {
					in.open(FullPath);
					if (!in) {
						MessageBox(NULL, TEXT("Ошибка чтения файла"), 0, MB_OK);
						return TRUE;
					}
					SendMessage(hList, LB_RESETCONTENT, 0, 0);
					int number;
					numbers.clear();
					while (in >> number)
						numbers.push_back(number);

					for (int number : numbers) {
						TCHAR s[10] = {0};
						_itot_s(number, s, 10);
						SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)s);
					}

					in.close();
				}
			}
			break;
		case ID_FILE_NEW:
			DialogBox(hi, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, CreateDlgProc);
			in.open("generated.txt");
			if (!in) {
				MessageBox(NULL, TEXT("Ошибка чтения файла"), 0, MB_OK);
				return TRUE;
			}
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			int number;
			numbers.clear();
			while (in >> number)
				numbers.push_back(number);

			for (int number : numbers) {
				TCHAR s[10] = { 0 };
				_itot_s(number, s, 10);
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)s);
			}

			in.close();
			break;
		case ID_FILE_EXIT:
			EndDialog(hWnd, 0);
			break;
		case IDC_BUTTON1:

			TCHAR result[300] = {0};
			if (numbers.size() != 0) {
				LRESULT lMin = SendMessage(hCheckBox1, BM_GETCHECK, 0, 0);
				if (lMin == BST_CHECKED) {
					int min = numbers[0];
					for (size_t i = 1; i < numbers.size(); i++) {
						if (numbers[i] < min)
							min = numbers[i];
					}
					lstrcat(result, TEXT("Минимальный элемент: "));
					TCHAR s[10] = { 0 };
					_itot_s(min, s, 10);
					lstrcat(result, s);
					lstrcat(result, TEXT("\r\n"));
				}
				LRESULT lMax = SendMessage(hCheckBox2, BM_GETCHECK, 0, 0);
				if (lMax == BST_CHECKED) {
					int max = numbers[0];
					for (size_t i = 1; i < numbers.size(); i++) {
						if (numbers[i] > max)
							max = numbers[i];
					}
					lstrcat(result, TEXT("Максимальный элемент: "));
					TCHAR s[10] = { 0 };
					_itot_s(max, s, 10);
					lstrcat(result, s);
				}
			}
			lstrcat(result, TEXT("Список пуст"));
			SetWindowText(hEdit, result);
			break;
		}


		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK CreateDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND hCombo;


	switch (message) {

	case WM_INITDIALOG:
		hCombo = GetDlgItem(hWnd, IDC_COMBO1);
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("5"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("7"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("10"));
		SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("14"));

		return TRUE;
	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case IDC_BUTTON1:
			int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			int count[] = { 5,7,10,14 };

			vector<int> result;
			for(int i = 0; i < count[index]; ++i) {
				result.push_back(rand() % 120);
			}
			wofstream out("generated.txt");
			if (!out) {
				MessageBox(NULL, TEXT("Ошибка чтения файла"), 0, MB_OK);
			}
			for(int i = 0; i < result.size(); ++i) {
				TCHAR s[10] = { 0 };
				_itot_s(result[i], s, 10);
				lstrcat(s, TEXT(" "));
				out << s;
			}
			EndDialog(hWnd, 0);
			return TRUE;
		}


		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}
