#pragma once
#include <iostream>
using namespace std;

// ���������� ���������
void bubleSort(int* Arr, int len);
// ����� �������
void printArray(int* Array, int len);
// ������� ��������� ����������
void twoCanal(int* a, int n);
// ��������� ������ ���������� �������
void randomFillArray(int* arr, const int size);
// ��������� ������ ������� �� �����������
void fillRightArray(int* arr, const int size);
// ��������� ������ ������� �� ��������
void fillBadArray(int* arr, const int size);
// ��������� ���� ����� �����
int intComparison(const int* i, const int* j);