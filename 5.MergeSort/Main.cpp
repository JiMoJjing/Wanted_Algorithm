#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MergeSort.h"

// ���� �Լ� ( Merge ).
// array: ���� �� �迭 ����.
// leftArray: ���� �迭 ����.
// leftArrayLength: ���� �迭 ���� ũ��.
// rightArray: ������ �迭 ����.
// rightArrayLength: ������ �迭 ���� ũ��.
void Merge(int* array,
	int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength)
{
	// �ε��� ����.
	int leftIndex = 0, rightIndex = 0, mergeIndex = 0;

	// ����/ ������ �迭�� ��Ҹ� ���ϸ鼭 ���� ������ array�� �� �Ҵ�.
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergeIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		else
		{
			array[mergeIndex] = rightArray[rightIndex];
			++rightIndex;
		}
		++mergeIndex;
	}

	// ���� ���Ұ� ������ �ֱ�.
	while (leftIndex < leftArrayLength)
	{
		array[mergeIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergeIndex;
	}

	while (rightIndex < rightArrayLength)
	{
		array[mergeIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergeIndex;
	}
}


// ���� �Լ� ( MergeSort ).
// length�� �������� ��� ������ ����.
void MergeSort(int* array, int length)
{
	// Ż�� ����.
	if (length <= 1)
	{
		return;
	}

	// �迭 ���� ( ������ ).
	int mid = length / 2;
	
	// ����/ ������ �迭�� ���� Ȯ��.
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	// �� ����.
	memcpy(leftArray, array, sizeof(int) * mid);
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	// ����� ȣ��.
	// ���� �迭�� ���� ��� ȣ��.
	MergeSort(leftArray, mid);
	
	// ������ �迭�� ���� ��� ȣ��.
	MergeSort(rightArray, length - mid);
	
	// ����.
	Merge(array, leftArray, mid, rightArray, length - mid);

	// �޸� ����.
	delete[] leftArray;
	delete[] rightArray;
}

// �迭 ��� �Լ�.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//// �迭.
	//int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	//// �迭 ����.
	//int length = sizeof(array) / sizeof(array[0]);

	//// ���� �� ���.
	//std::cout << "���� �� �迭: ";
	//PrintArray(array, length);

	//// ����.
	//MergeSort(array, length);

	//// ���� �� ���.
	//std::cout << "���� �� �迭: ";
	//PrintArray(array, length);

	// �迭.
	double array[] = { 10.0, 11.2, 2.3, 6.5, 5.4, 5.3, 1.2, 123.3, 22.2 };

	// �迭 ����.
	int length = sizeof(array) / sizeof(array[0]);

	// ���� �� ���.
	std::cout << "���� �� �迭: ";
	PrintArray<double>(array, length);

	// ����.
	MergeSort<double>(array, length);

	// ���� �� ���.
	std::cout << "���� �� �迭: ";
	PrintArray<double>(array, length);

	std::cin.get();
}