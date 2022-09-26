#include "Header.h"
#include <time.h> 

int main() {
	int bubleArray[] = { 100, 3, 4, 6, 0, 1, 1, 12, 0, -2 };
	int twoCanalArray[] = { 100, 3, 4, 6, 0, 1, 1, 12, 0, -2 };
	int arrayLen = sizeof(bubleArray) / sizeof(bubleArray[0]);

	cout << "Array: ";
	printArray(bubleArray, arrayLen);
	
	cout << "\nStart with bubleSort";
	clock_t startBuble, finishBuble, startCanal, finishCanal;
	startBuble = clock();
	bubleSort(bubleArray, arrayLen);
	finishBuble = clock() - startBuble;
	cout << "\ntime with bubleSort: " << finishBuble << "\n";
	
	printArray(bubleArray, arrayLen);
	cout << "\nStart with twoCanalSort\n";
	startCanal = clock();
	twoCanal(twoCanalArray, arrayLen);
	finishCanal = clock() - startBuble;
	printArray(twoCanalArray, arrayLen);
	cout << "\ntime with canalSort: " << finishCanal << "\n";
 	
	return 0;
}