#include <iostream>

// �� ���� ���� ��ȯ�ϴ� �Լ�.
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

// ���� ���� �Լ�.
//void BubbleSort(int* array, int length)
//{
//	// ����.
//	for (int ix = 0; ix < length - 1; ++ix)
//	{
//		for (int jx = 0; jx < length - 1; ++jx)
//		{
//			if (array[jx] > array[jx + 1])
//			{
//				Swap(array[jx], array[jx + 1]);
//			}
//		}
//	}
//}

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

void BubbleSort(int* array, int length, Compare comp)
{
	// ����.
	for (int ix = 0; ix < length - 1; ++ix)
	{
		for (int jx = 0; jx < length - 1; ++jx)
		{
			if (!comp(array[jx], array[jx + 1]))
			{
				Swap(array[jx], array[jx + 1]);
			}
		}
	}
}

int main()
{
	// �ڷ� ����.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	PrintArray(array, sizeof(array) / sizeof(int));
	
	BubbleSort(array, sizeof(array) / sizeof(int), [](int a, int b)->bool { return a > b; });
	
	PrintArray(array, sizeof(array) / sizeof(int));

	BubbleSort(array, sizeof(array) / sizeof(int), [](int a, int b)->bool { return a < b; });

	PrintArray(array, sizeof(array) / sizeof(int));
	
	std::cin.get();
}