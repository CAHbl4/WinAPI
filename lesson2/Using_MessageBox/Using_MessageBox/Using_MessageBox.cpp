#include <windows.h>
#include<tchar.h>
#include <ctime>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hIprev, LPTSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));
	int number = rand() % 100;
	int n1 = 50;
	int n2=n1/2;
	int otvet;
	TCHAR str[20];
	//формирование строки дл€ вывода
	wsprintf(str, L"Ёто число %d", n1);
	while (true)
	{
		if (n1 == number)
		{
			wsprintf(str, L"Ёто число %d", n1);
			otvet = MessageBox(NULL, str, _T("”гадайц число"), MB_OKCANCEL | MB_ICONINFORMATION);
			break;
		}
		else
		{
			if (n1 < number)
			{
				wsprintf(str, L"Ёто число >%d", n1);
				otvet = MessageBox(NULL, str, _T("”гадай число"), MB_OKCANCEL | MB_ICONINFORMATION);
				n1 += n2;
			}
			else
			{
				wsprintf(str, L"Ёто число <%d", n1);
				otvet = MessageBox(NULL, str, _T("”гадай число"), MB_OKCANCEL | MB_ICONINFORMATION);
				n1 -= n2;
			}
			if (n2>1)
			n2 = n2 / 2;
		}
	}
	
	return 0;
}
