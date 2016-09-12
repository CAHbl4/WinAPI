// Unicode.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include"tcout.h"
#include <windows.h>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	//������������� ��������� ANSI
	char ch = 'A';
	cout << "ch=" << ch << endl;
	char* str1 = "Hello!!!";
	cout << "str1=" << str1 << endl;
	char str2[256];
	str2[0] = '\0';
	strcat_s(str2, 256, str1);
	cout << "str2=" << str2 << endl;

	//������������� ��������� Unicode
	wchar_t wch = 'A';
	//��� ������ ������������ wcout
	wcout << "wch=" << wch << endl;
	wchar_t* wstr1 = L"������";
	wcout << "wstr1=" << wstr1 << endl;
	wchar_t wstr2[256]=L"Hi-";
	wcscat_s(wstr2, 256, wstr1);
	wcout << "wstr2=" << wstr2 << endl;

	//������������� ������� _TCHAR
	//TCHAR  
	_TCHAR tch = 'B';
	wcout << "tch=" << tch << endl;
	TCHAR* tstr1 = _TEXT("��� ����?");
	wcout << tstr1 << endl;

	// ANSI-���������
	char szBuf1[15] = "Hello,";
	strcat_s(szBuf1, 15, " world!");
	cout << "Ansi: " << szBuf1 <<", size:"<< sizeof(szBuf1) << " bytes\n";

	// UNICODE-���������
	wchar_t szBuf2[15] = L"Hello,";
	wcscat_s(szBuf2, 15, L" world!");
	wcout << "Unicode: " << szBuf2 <<", size:"<< sizeof(szBuf2) << " bytes\n";

	//������� ������ �� ANSI � UNICODE
	char strANSI[] = "������ ANSI";
	//���������� ����� Unicode ������ 
	int length = MultiByteToWideChar(CP_ACP, 0, strANSI, -1, NULL, 0);
	//�������� ������
	wchar_t *ptr = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, strANSI, -1, ptr, length);
	cout << "ANSI:" << strANSI << endl;
	wcout << "UNICODE:" << ptr << endl;
	delete[] ptr;

	//�������������� ������� mbstowcs
	cout << "-------------------------------\n";
	char buffer1[] = "mbstowcs converts ANSI-string to Unicode-string";
	// ��������� ������ ������, ����������� ��� �������� Unicode-������
	int length1 = strlen(buffer1) + 1;
	ptr = new wchar_t[length1];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, ptr, length1,buffer1, _TRUNCATE);
	cout << "ANSI:" << buffer1 << endl;
	wcout << "UNICODE:" << ptr << endl;
	delete[] ptr;

	cout << "===============================================\n";
	//�������������� UNICODE ������ � ANSI
	wchar_t* strUNICODE = L"������ UNICODE";
	//������������� ������� WideCharToMultiByte
	length = wcslen(strUNICODE)+1;
	cout << "Length=" << length<<endl;
	char *ptr1 = new char[length];
	WideCharToMultiByte(CP_ACP, 0, strUNICODE, -1, ptr1, length, 0, 0);
	wcout << "UNICODE:" <<strUNICODE  << endl;
	cout << "ANSI:" << ptr1 << endl;
	delete[] ptr1;

	//������������� ������� wcstombs
	wchar_t buffer2[] = L"wcstombs converts Unicode-string to ANSI-string";
	// ��������� ������ ������, ����������� ��� �������� ��������������� ANSI-������
	length1 = wcslen(buffer2)+1;
	ptr1 = new char[length1];
	// ������������ Unicode-������ � ANSI-������ 
	wcstombs_s(&convertedChars, ptr1, length1, buffer2, _TRUNCATE);
	wcout << "UNICODE:" << buffer2 << endl;
	cout << "ANSI:" << ptr1 << endl;
	delete[] ptr1;







	
	system("pause");
	return 0;
}

