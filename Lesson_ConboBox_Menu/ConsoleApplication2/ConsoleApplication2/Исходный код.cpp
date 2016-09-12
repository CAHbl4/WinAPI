/*1.	ѕодсчитать количество слов во введенном предложении.
a)	* между словами находитс€ только 1 пробел*/

#include<iostream>
using namespace std;


void main()
{
	int k = 1;
	char message[] = "Iam study programming in STEP b b b b";
	char *ptr = message;

	while (*ptr != '\0')
	{
		if (*ptr == ' ')
		{
			k++;
		}
		ptr++;
	}

	cout << "Kolichestvo slov ravno: " << k;
	cout << "\n\n";

}
