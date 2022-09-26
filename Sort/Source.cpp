#include "Header.h"

void helloWorld() {
	cout << "Hello World";
}

void bubleSort(int* Arr, int len) {
	int t;
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