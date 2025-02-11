#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MergeSort.h"

// 병합 함수 ( Merge ).
// array: 병합 할 배열 변수.
// leftArray: 왼쪽 배열 변수.
// leftArrayLength: 왼쪽 배열 변수 크기.
// rightArray: 오른쪽 배열 변수.
// rightArrayLength: 오른쪽 배열 변수 크기.
void Merge(int* array,
	int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength)
{
	// 인덱스 생성.
	int leftIndex = 0, rightIndex = 0, mergeIndex = 0;

	// 왼쪽/ 오른쪽 배열의 요소를 비교하면서 작은 순서로 array에 값 할당.
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

	// 남은 원소가 있으면 넣기.
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


// 정렬 함수 ( MergeSort ).
// length를 기준으로 계속 반으로 나눔.
void MergeSort(int* array, int length)
{
	// 탈출 조건.
	if (length <= 1)
	{
		return;
	}

	// 배열 분할 ( 나누기 ).
	int mid = length / 2;
	
	// 왼쪽/ 오른쪽 배열의 공간 확보.
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	// 값 복사.
	memcpy(leftArray, array, sizeof(int) * mid);
	memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

	// 재귀적 호출.
	// 왼쪽 배열에 대해 재귀 호출.
	MergeSort(leftArray, mid);
	
	// 오른쪽 배열에 대해 재귀 호출.
	MergeSort(rightArray, length - mid);
	
	// 병합.
	Merge(array, leftArray, mid, rightArray, length - mid);

	// 메모리 해제.
	delete[] leftArray;
	delete[] rightArray;
}

// 배열 출력 함수.
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

	//// 배열.
	//int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	//// 배열 길이.
	//int length = sizeof(array) / sizeof(array[0]);

	//// 정렬 전 출력.
	//std::cout << "정렬 전 배열: ";
	//PrintArray(array, length);

	//// 정렬.
	//MergeSort(array, length);

	//// 정렬 후 출력.
	//std::cout << "정렬 후 배열: ";
	//PrintArray(array, length);

	// 배열.
	double array[] = { 10.0, 11.2, 2.3, 6.5, 5.4, 5.3, 1.2, 123.3, 22.2 };

	// 배열 길이.
	int length = sizeof(array) / sizeof(array[0]);

	// 정렬 전 출력.
	std::cout << "정렬 전 배열: ";
	PrintArray<double>(array, length);

	// 정렬.
	MergeSort<double>(array, length);

	// 정렬 후 출력.
	std::cout << "정렬 후 배열: ";
	PrintArray<double>(array, length);

	std::cin.get();
}