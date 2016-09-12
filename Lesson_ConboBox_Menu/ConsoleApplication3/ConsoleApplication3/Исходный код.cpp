/*3.Написать программу, которая заменяет все символы точки «.» в строке,
введенной пользователем, на символы восклицательного знака «!»*/

#include<iostream>
#include<stdio.h>
using namespace std;

void zamena(char A[], int size)
{
	char*ptr = A;

	while (*ptr != '\0')
	{
		if (*ptr == '.')
		{
			*ptr = '!';
		}

		ptr++;
	}

}

void vivod_massiva(char A[], int size)
{
	char*ptr = A;

	while (*ptr != '\0')
	{
		cout << *ptr;
		ptr++;
	}

}


void main()
{
	int k = 0;
	int size = 100000000;
	char message[] = " I..a.m. .s.t.udy.  . p.r.o.gramming.  . .in .  .STE.P .  .v.e.r.y. .  good     ";
	char *ptr = message;

	zamena(message, size);
	vivod_massiva(message, size);

}
