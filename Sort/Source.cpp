#include "Header.h"
#include <stdio.h>
#include <time.h>

void bubleSort(int* Arr, int len) {
	int t;
	//#pragma omp parallel for
	for (int i = 0; i < len - 1;) {
		if (Arr[i] > Arr[i + 1]) {
			t = Arr[i];
			Arr[i] = Arr[i + 1];
			Arr[i + 1] = t;
			i = 0;
			continue;
		}
		++i;
	}
}

void printArray(int* Array, int len) {
	for (int i = 0; i < len; i++) {
		cout << Array[i] << " ";
	}
}

void twoCanal(int* ar, int lng) {
	#pragma omp parallel for
	for (int lfI = 0, rgI = lng - 1; lfI < rgI;) {
		for (int i = lfI; i < rgI; ++i)
			if (ar[i + 1] < ar[i])
				swap(ar[i], ar[i + 1]);
		rgI--;

		for (int i = rgI; i > lfI; --i)
			if (ar[i - 1] > ar[i])
				swap(ar[i - 1], ar[i]);
		lfI++;
	}
}

void randomFillArray(int* arr, const int size) {
	for (int i = 0; i < size; i++)
		arr[i] = 1 + rand() % 1000;
}

void fillRightArray(int* arr, const int size) {
	for (int i = 0; i < size; i++)
		arr[i] = i;
}

void fillBadArray(int* arr, const int size) {
	for (int i = 0; i < size; i++)
		arr[i] = size - i;
}

int intComparison(const int* i, const int* j) {
	return *i - *j;
}