#include <iostream>
#include <omp.h>
#include <fstream>

using namespace std;
#define N_ELEM 100000
int arr[N_ELEM];
#define N_THREAD 4

void _sort(int* arr, int left, int right)
{

	int i = left, j = right;
	int tmp;
	int mid = arr[(left + right) / 2];

	while (i <= j) {
		while (arr[i] < mid) {
			i++;
		}
		while (arr[j] > mid) {
			j--;
		}
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}


	if (((right - left) < (N_ELEM / N_THREAD))) {
		if (left < j) {
			_sort(arr, left, j);
		}
		if (i < right) {
			_sort(arr, i, right);
		}

	}
	else {
#pragma omp task
		{
			_sort(arr, left, j);
		}
#pragma omp task
		{
			_sort(arr, i, right);
		}
	}
}

void sort(int* array) {
#pragma omp parallel num_threads(N_THREAD)
	{
#pragma omp single nowait
		{
			_sort(array, 0, N_ELEM - 1);
		}
	}
}

int main(int argc, char* argv[]) {
	arr[561] = 2;
	arr[111] = 1;
	double start_time = omp_get_wtime();
	sort(arr);
	double end_time = omp_get_wtime();

	cout << "time: " << end_time - start_time << endl;

	for(int i = N_ELEM - 10; i < N_ELEM; i++){
		cout << arr[i] << " ";
	}

	return 0;
}
