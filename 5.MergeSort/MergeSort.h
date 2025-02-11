#pragma once

template<typename T>
void Merge(T* array, T* leftArray, int leftArrayLength, T* rightArray, int rightArrayLength)
{
	// 인덱스 생성.
	int mergeIndex = 0, leftIndex = 0, rightIndex = 0;

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
		++mergeIndex;
		++leftIndex;
	}
	while (rightIndex < rightArrayLength)
	{
		array[mergeIndex] = rightArray[rightIndex];
		++mergeIndex;
		++rightIndex;
	}
}

template<typename T>
void MergeSort(T* array, int length)
{
	// 탈출 조건.
	if (length <= 1)
	{
		return;
	}
	
	// 배열 분할 ( 나누기 ).
	int mid = length / 2;
	
	// 왼쪽/ 오른쪽 배열의 공간 확보.
	T* leftArray = new T[mid];
	T* rightArray = new T[length - mid];
	
	// 값 복사.
	memcpy(leftArray, array, sizeof(T) * mid);
	memcpy(rightArray, array + mid, sizeof(T) * (length - mid));

	// 재귀적 호출.
	// 왼쪽 배열에 대해 재귀 호출.
	MergeSort<T>(leftArray, mid);
	// 오른쪽 배열에 대해 재귀 호출.
	MergeSort<T>(rightArray, length - mid);

	// 병합.
	Merge<T>(array, leftArray, mid, rightArray, length - mid);

	// 메모리 해제.
	delete[] leftArray;
	delete[] rightArray;
}

// 배열 출력 함수.
template<typename T>
void PrintArray(T array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}
