/*
1. „ерез указатели на указатели посчитать сумму двух
чисел и записать в третье.
*/
#include<stdio.h>
#include<iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int sum(int **, int **);

void main()
{
	setlocale(LC_ALL, "Russian");

	int a = 0, b = 0, res = 0;
	int *pa, *pb;
	pa = &a;
	pb = &b;
	int **ppa = &pa;
	int **ppb = &pb;

	//через printf scanf
	printf("¬ведите первое значение\n");
	scanf("%d", *ppa);
	printf("¬ведите второе значение\n");
	scanf("%d", *ppb);

	res = **ppa + **ppb;
	printf("—умма = %d\n", res);

	//через cin cout
	cout << "¬ведите первое значение\n";
	cin >> **ppa;
	cout << "¬ведите второе значение\n";
	cin >> **ppb;

	res = *pa + *pb;
	cout << "—умма = " << res << endl;

	//через функцию
	cout << "¬ведите первое значение\n";
	cin >> **ppa;
	cout << "¬ведите второе значение\n";
	cin >> **ppb;

	res = sum(ppa, ppb);
	printf("—умма = %d\n", res);

	cout << endl;
}
int sum(int **a, int **b)
{
	int res = **a + **b;
	return res;
}