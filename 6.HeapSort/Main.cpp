#include <iostream>
#include <vector>

// 힙 만들기 ( Heapify ) 함수.
void heapify(std::vector<int>& array, int length, int ix)
{
    while (true)
    {
        // 힙 구성을 위한 인덱스 변수.
        int largest = ix;

        // 왼쪽 자손 인덱스.
        int left = 2 * ix + 1;

        // 오른쪽 자손 인덱스.
        int right = 2 * ix + 2;

        if (left < length && array[left] > array[largest])
        {
            largest = left;
        }

        if (right < length && array[right] > array[largest])
        {
            largest = right;
        }

        if (largest == ix)
        {
            break;
        }

        std::swap(array[ix], array[largest]);
        ix = largest;
    }

}


// 힙 정렬 함수 ( HeapSort ).
void HeapSort(std::vector<int>& array)
{
    // 전체 크기.
    int length = (int)array.size();

    // 힙 구성.
    for (int ix = length / 2 - 1; ix >= 0; --ix)
    {
        // 힙 만들기.
        heapify(array, length, ix);
    }

    // 정렬.
    for (int ix = length - 1; ix > 0; --ix)
    {
        std::swap(array[0], array[ix]);
        heapify(array, ix, 0);      
    }
}

// 배열 출력 함수.
void PrintArray(std::vector<int>& array)
{
    for (int ix = 0; ix < array.size(); ++ix)
    {
        std::cout << array[ix] << (ix < array.size() - 1 ? ", " : "");
    }

    std::cout << "\n";
}


int main()
{
	// 배열.
	std::vector<int> array = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    HeapSort(array);

    PrintArray(array);
}