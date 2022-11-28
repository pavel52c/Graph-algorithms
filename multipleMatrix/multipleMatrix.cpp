#include <iostream>
#include <omp.h>
using namespace std;

void printMatrix(int** matrix, size_t size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n";
}

void fillMatrix(int** &matrix, size_t size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix[i][j] = rand()%10;
		}
	}
}

int** classicMatrixMultiple(int** matrixFirst, int** matrixSecond, size_t size) {
	int** result = new int* [size];
	for (int i = 0; i < size; i++){
		result[i] = new int[size];
		for (int j = 0; j < size; j++) {
			result[i][j] = 0;
			for (int k = 0; k < size; k++) {
				result[i][j] = result[i][j] + matrixFirst[i][k] * matrixSecond[k][j];
			}
		}
	}
	return result;
}

int** parallelClassicMatrixMultiple(int** matrixFirst, int** matrixSecond, size_t size) {
	const int treadsCount = 12;
	omp_set_num_threads(treadsCount);

	int** result = new int* [size];
	#pragma omp parallel
{
		int i, j, k;
		#pragma omp for
		for (i = 0; i < size; i++) {
			result[i] = new int[size];
			for (j = 0; j < size; j++) {
				result[i][j] = 0;
				for (k = 0; k < size; k++) {
					result[i][j] = result[i][j] + matrixFirst[i][k] * matrixSecond[k][j];
				}
			}
		}
	}
	return result;
}

int** vinogradMatrixMultiple(int** matrixFirst, int** matrixSecond, size_t size) {
	int** result = new int* [size];
	size_t halfSize = size / 2;
	int i, j, k;
	
	int* Ai = new int[size];
	int* Bj = new int[size];

	for (i = 0; i < size; i++) {
		Ai[i] = 0;
		Bj[i] = 0;
		result[i] = new int[size];
		for (j = 0; j < halfSize; j++) {
			Ai[i] = Ai[i] + matrixFirst[i][2 * j] * matrixFirst[i][2 * j + 1];
			Bj[i] = Bj[i] + matrixSecond[2 * j][i] * matrixSecond[2 * j + 1][i];
			result[i][j] = 0;
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			result[i][j] = (-1) * Ai[i] - Bj[j];
			for (k = 0; k< halfSize; k++) {
				result[i][j] = result[i][j] + (matrixFirst[i][2 * k] + matrixSecond[2 * k + 1][j]) * (matrixFirst[i][2 * k + 1] + matrixSecond[2 * k][j]);
			}
		}
	}
	return result;
}

int** parallelVinogradMatrixMultiple(int** matrixFirst, int** matrixSecond, size_t size) {
	const int treadsCount = 12;
	omp_set_num_threads(treadsCount);

	int** result = new int* [size];
	size_t halfSize = size / 2;

	int* Ai = new int[size];
	int* Bj = new int[size];

	for (int i = 0; i < size; i++) {
		Ai[i] = 0;
		Bj[i] = 0;
		result[i] = new int[size];
		for (int j = 0; j < halfSize; j++) {
			Ai[i] = Ai[i] + matrixFirst[i][2 * j] * matrixFirst[i][2 * j + 1];
			Bj[i] = Bj[i] + matrixSecond[2 * j][i] * matrixSecond[2 * j + 1][i];
			result[i][j] = 0;
		}
	}
	#pragma omp parallel
	{
		int i, j, k;
		#pragma omp for private(i, j, k)
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				result[i][j] = (-1) * Ai[i] - Bj[j];
				for (k = 0; k < halfSize; k++) {
					result[i][j] = result[i][j] + (matrixFirst[i][2 * k] + matrixSecond[2 * k + 1][j]) * (matrixFirst[i][2 * k + 1] + matrixSecond[2 * k][j]);
				}
			}
		}
	}
	return result;
}

void callMultiple(int** (*func)(int**first, int** second, size_t size), int** first, int** second, size_t size, bool print = false) {
	clock_t start, end;
	start = clock();
	int** result = func(first, second, size);
	end = clock();
	if (print)
	{
		cout << "Результат умножения: " << endl;
		printMatrix(result, size);
	}
	cout << "Умножение заняло: " << end - start << "мсек\n";
	cout << endl;
}

void checkProgram(size_t size = 4, bool parallel = false) {
	int** firstMatrix = new int* [size];
	int** secondMatrix = new int* [size];
	for (int i = 0; i < size; i++) {
		firstMatrix[i] = new int[size];
		secondMatrix[i] = new int[size];
	}
	fillMatrix(firstMatrix, size);
	fillMatrix(secondMatrix, size);
	printMatrix(firstMatrix, size);
	cout << "\n";
	printMatrix(secondMatrix, size);
	cout << "\n";
	callMultiple(parallel ? parallelClassicMatrixMultiple : classicMatrixMultiple , firstMatrix, secondMatrix, size, true);
	callMultiple(parallel ? parallelVinogradMatrixMultiple : vinogradMatrixMultiple, firstMatrix, secondMatrix, size, true);
}

int main() {
	size_t array_sizes[] = { 50, 100, 200, 500, 1000 };
	
	setlocale(LC_ALL, "Russian");
	//checkProgram();
	//checkProgram(true);
	for (size_t size : array_sizes) {
		int** firstMatrix = new int* [size];
		int** secondMatrix = new int* [size];
		for (int i = 0; i < size; i++) {
			firstMatrix[i] = new int[size];
			secondMatrix[i] = new int[size];
		}
		fillMatrix(firstMatrix, size);
		fillMatrix(secondMatrix, size);

		cout << "Size: " << size << "\n";
		cout << "classicMatrixMultiple: " << endl;
		callMultiple(classicMatrixMultiple, firstMatrix, secondMatrix, size);
		cout << "parallelClassicMatrixMultiple: " << endl;
		callMultiple(parallelClassicMatrixMultiple, firstMatrix, secondMatrix, size);
		cout << "vinogradMatrixMultiple: " << endl;
		callMultiple(vinogradMatrixMultiple, firstMatrix, secondMatrix, size);
		cout << "parallelVinogradMatrixMultiple: " << endl;
		callMultiple(parallelVinogradMatrixMultiple, firstMatrix, secondMatrix, size);
	}
}
