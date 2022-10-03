#include "Header.h"
#include <time.h>  

int main() {
	const int arrayLen = 10000;
	clock_t start, end;

	int* bubleArray = new int[arrayLen];
	int* twoCanalArray = new int[arrayLen];
	int* qsortArray = new int[arrayLen];
	// Заполнение массива различными наборами данных
	randomFillArray(bubleArray, arrayLen);
	randomFillArray(twoCanalArray, arrayLen);
	randomFillArray(qsortArray, arrayLen);

	// Проводим замеры
	start = clock();
	bubleSort(bubleArray, arrayLen);
	end = clock();
	cout << "Time for buble sort: " << end - start << '\n' << endl;

	start = clock();
	twoCanal(twoCanalArray, arrayLen);
	end = clock();
	cout << "Time for twoCanal: " << end - start << '\n' << endl;

	start = clock();
	#pragma omp parallel for
	qsort(qsortArray, arrayLen, sizeof(int), (int(*) (const void*, const void*)) intComparison);
	end = clock();
	cout << "Time for qsort: " << end - start << '\n' << endl;

	return 0;
}