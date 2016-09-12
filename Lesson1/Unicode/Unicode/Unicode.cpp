// Unicode.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include"tcout.h"
#include <windows.h>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	//использование кодировки ANSI
	char ch = 'A';
	cout << "ch=" << ch << endl;
	char* str1 = "Hello!!!";
	cout << "str1=" << str1 << endl;
	char str2[256];
	str2[0] = '\0';
	strcat_s(str2, 256, str1);
	cout << "str2=" << str2 << endl;

	//использование кодировки Unicode
	wchar_t wch = 'A';
	//для вывода используется wcout
	wcout << "wch=" << wch << endl;
	wchar_t* wstr1 = L"Привет";
	wcout << "wstr1=" << wstr1 << endl;
	wchar_t wstr2[256]=L"Hi-";
	wcscat_s(wstr2, 256, wstr1);
	wcout << "wstr2=" << wstr2 << endl;

	//использование макроса _TCHAR
	//TCHAR  
	_TCHAR tch = 'B';
	wcout << "tch=" << tch << endl;
	TCHAR* tstr1 = _TEXT("Как дела?");
	wcout << tstr1 << endl;

	// ANSI-кодировка
	char szBuf1[15] = "Hello,";
	strcat_s(szBuf1, 15, " world!");
	cout << "Ansi: " << szBuf1 <<", size:"<< sizeof(szBuf1) << " bytes\n";

	// UNICODE-кодировка
	wchar_t szBuf2[15] = L"Hello,";
	wcscat_s(szBuf2, 15, L" world!");
	wcout << "Unicode: " << szBuf2 <<", size:"<< sizeof(szBuf2) << " bytes\n";

	//перевод строки из ANSI в UNICODE
	char strANSI[] = "Строка ANSI";
	//определяем длину Unicode строки 
	int length = MultiByteToWideChar(CP_ACP, 0, strANSI, -1, NULL, 0);
	//выделяем память
	wchar_t *ptr = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, strANSI, -1, ptr, length);
	cout << "ANSI:" << strANSI << endl;
	wcout << "UNICODE:" << ptr << endl;
	delete[] ptr;

	//использоваание функции mbstowcs
	cout << "-------------------------------\n";
	char buffer1[] = "mbstowcs converts ANSI-string to Unicode-string";
	// определим размер памяти, необходимый для хранения Unicode-строки
	int length1 = strlen(buffer1) + 1;
	ptr = new wchar_t[length1];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, ptr, length1,buffer1, _TRUNCATE);
	cout << "ANSI:" << buffer1 << endl;
	wcout << "UNICODE:" << ptr << endl;
	delete[] ptr;

	cout << "===============================================\n";
	//преобразование UNICODE строки в ANSI
	wchar_t* strUNICODE = L"Строка UNICODE";
	//использование функции WideCharToMultiByte
	length = wcslen(strUNICODE)+1;
	cout << "Length=" << length<<endl;
	char *ptr1 = new char[length];
	WideCharToMultiByte(CP_ACP, 0, strUNICODE, -1, ptr1, length, 0, 0);
	wcout << "UNICODE:" <<strUNICODE  << endl;
	cout << "ANSI:" << ptr1 << endl;
	delete[] ptr1;

	//использование функции wcstombs
	wchar_t buffer2[] = L"wcstombs converts Unicode-string to ANSI-string";
	// Определим размер памяти, необходимый для хранения преобразованной ANSI-строки
	length1 = wcslen(buffer2)+1;
	ptr1 = new char[length1];
	// конвертируем Unicode-строку в ANSI-строку 
	wcstombs_s(&convertedChars, ptr1, length1, buffer2, _TRUNCATE);
	wcout << "UNICODE:" << buffer2 << endl;
	cout << "ANSI:" << ptr1 << endl;
	delete[] ptr1;







	
	system("pause");
	return 0;
}

