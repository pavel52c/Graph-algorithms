#include "Header.h"
#include <time.h>  

int main() {
	const int arrayLen = 10;
	clock_t start, end;

	int bubleArray[10] = {355, 736, 828, 342, 320, 314, 710, 257, 849, 446};
	int twoCanalArray[10] = { 230, 318, 432, 509, 431, 938, 798, 8, 259, 324 };
	int qsortArray[10] = { 94, 434, 67, 412, 238, 433, 185, 609, 611, 216 };

	/*randomFillArray(bubleArray, arrayLen);
	randomFillArray(twoCanalArray, arrayLen);
	randomFillArray(qsortArray, arrayLen);*/

	//cout << "BubleArray: ";
	printArray(bubleArray, arrayLen);
	start = clock();
	bubleSort(bubleArray, arrayLen);
	end = clock();
	cout << "Time for buble sort: " << end - start << endl;
	printArray(bubleArray, arrayLen);
	cout << '\n';


	//cout << "twoCanalArray: ";
	printArray(twoCanalArray, arrayLen);
	start = clock();
	twoCanal(twoCanalArray, arrayLen);
	end = clock();
	cout << "Time for twoCanal: " << end - start << endl;
	printArray(twoCanalArray, arrayLen);
	cout << '\n';


	//cout << "qsortArray: ";
	printArray(qsortArray, arrayLen);
	start = clock();
	//#pragma omp parallel for
	qsort(qsortArray, arrayLen, sizeof(int), (int(*) (const void*, const void*)) intComparison);
	end = clock();
	cout << "Time for qsort: " << end - start << endl;
	printArray(qsortArray, arrayLen);
	cout << '\n';

	return 0;
}