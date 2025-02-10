#include <iostream>
#include <time.h>

// ���� ���� �Լ�.
void SelectionSort(int* array, int length)
{
	// ����.
	for (int ix = 0; ix < length - 1; ++ix)
	{
		// �ּҰ� ������ ����.
		int minIndex = ix;

		for (int jx = ix + 1; jx < length; ++jx)
		{
			// ��.
			if (array[jx] < array[minIndex])
			{
				minIndex = jx;
			}

		}

		// �� �ٲٱ�.
		std::swap(array[ix], array[minIndex]);
	}
}

// ��� �Լ�.
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
	// �ڷ� ����.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	PrintArray(array, sizeof(array) / sizeof(int));
	int start = clock();
	SelectionSort(array, sizeof(array) / sizeof(int));
	int end = clock();

	PrintArray(array, sizeof(array) / sizeof(int));

	std::cout << "�ð�: " << end - start;

	std::cin.get();
}