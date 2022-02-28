// Transpose_2dArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void printMatrix(int** ptr, size_t N, size_t M) {
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < M; ++j) {
			std::cout<< ptr[i][j]<<" ";
		}
		std::cout << std::endl;
	}
}

int** transpose(int** matrix, size_t N, size_t M) {
	int** temp = new int* [M];
	for (size_t i = 0; i < M; ++i) {
		temp[i] = new int[N];
	}

	for (size_t i = 0; i < M; ++i) {
		for (size_t j = 0; j < N; ++j) {
			temp[i][j] = matrix[j][i];
		}
	}
	return temp;
}


int main()
{
	size_t N, M;
	std::cin >> N >> M;
	int** matrix = new int* [N];
	//Allocate dynamic memory or M*N ints in the heap
	for (size_t i = 0; i < N; ++i) {
		matrix[i] = new int[M];
	}

	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < M; ++j) {
			std::cin >> matrix[i][j];
		}
	}

	int** matrix_transpose = transpose(matrix, N, M);
	printMatrix(matrix, N, M);
	for (size_t i = 0; i < N; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	std::cout << std::endl;
	printMatrix(matrix_transpose, M, N);
	for (size_t i = 0; i < M; ++i) {
		delete[] matrix_transpose[i];
	}
	delete[] matrix_transpose;
	return 0;
}
