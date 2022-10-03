#pragma once
#include <iostream>
using namespace std;

// Сортировка пузырьком
void bubleSort(int* Arr, int len);
// Вывод массива
void printArray(int* Array, int len);
// Функция шейкерной сортировки
void twoCanal(int* a, int n);
// Заполняет массив случайными числами
void randomFillArray(int* arr, const int size);
// Заполняет массив числами по возрастанию
void fillRightArray(int* arr, const int size);
// Заполняет массив числами по убыванию
void fillBadArray(int* arr, const int size);
// Сравнение двух целых чисел
int intComparison(const int* i, const int* j);