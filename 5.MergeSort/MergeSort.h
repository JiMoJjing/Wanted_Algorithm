#pragma once

template<typename T>
void Merge(T* array, T* leftArray, int leftArrayLength, T* rightArray, int rightArrayLength)
{
	// �ε��� ����.
	int mergeIndex = 0, leftIndex = 0, rightIndex = 0;

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
	// Ż�� ����.
	if (length <= 1)
	{
		return;
	}
	
	// �迭 ���� ( ������ ).
	int mid = length / 2;
	
	// ����/ ������ �迭�� ���� Ȯ��.
	T* leftArray = new T[mid];
	T* rightArray = new T[length - mid];
	
	// �� ����.
	memcpy(leftArray, array, sizeof(T) * mid);
	memcpy(rightArray, array + mid, sizeof(T) * (length - mid));

	// ����� ȣ��.
	// ���� �迭�� ���� ��� ȣ��.
	MergeSort<T>(leftArray, mid);
	// ������ �迭�� ���� ��� ȣ��.
	MergeSort<T>(rightArray, length - mid);

	// ����.
	Merge<T>(array, leftArray, mid, rightArray, length - mid);

	// �޸� ����.
	delete[] leftArray;
	delete[] rightArray;
}

// �迭 ��� �Լ�.
template<typename T>
void PrintArray(T array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}
