/*
1. ����� ��������� �� ��������� ��������� ����� ����
����� � �������� � ������.
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

	//����� printf scanf
	printf("������� ������ ��������\n");
	scanf("%d", *ppa);
	printf("������� ������ ��������\n");
	scanf("%d", *ppb);

	res = **ppa + **ppb;
	printf("����� = %d\n", res);

	//����� cin cout
	cout << "������� ������ ��������\n";
	cin >> **ppa;
	cout << "������� ������ ��������\n";
	cin >> **ppb;

	res = *pa + *pb;
	cout << "����� = " << res << endl;

	//����� �������
	cout << "������� ������ ��������\n";
	cin >> **ppa;
	cout << "������� ������ ��������\n";
	cin >> **ppb;

	res = sum(ppa, ppb);
	printf("����� = %d\n", res);

	cout << endl;
}
int sum(int **a, int **b)
{
	int res = **a + **b;
	return res;
}