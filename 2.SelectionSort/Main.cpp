#include <iostream>
#include <time.h>

// 선택 정렬 함수.
void SelectionSort(int* array, int length)
{
	// 정렬.
	for (int ix = 0; ix < length - 1; ++ix)
	{
		// 최소값 저장할 변수.
		int minIndex = ix;

		for (int jx = ix + 1; jx < length; ++jx)
		{
			// 비교.
			if (array[jx] < array[minIndex])
			{
				minIndex = jx;
			}

		}

		// 값 바꾸기.
		std::swap(array[ix], array[minIndex]);
	}
}

// 출력 함수.
void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << " ";
	}
	std::cout << "\n";
}

using Compare = bool(*)(int, int);

int main()
{
	// 자료 집합.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	PrintArray(array, sizeof(array) / sizeof(int));
	int start = clock();
	SelectionSort(array, sizeof(array) / sizeof(int));
	int end = clock();

	PrintArray(array, sizeof(array) / sizeof(int));

	std::cout << "시간: " << end - start;

	std::cin.get();
}