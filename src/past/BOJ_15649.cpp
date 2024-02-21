// 2023-10-05T16:17
#include <iostream>

void RecurPointer(int* ArrayStart, int* ArrayEnd, int** PointerStart, int** PointerEnd, int** PointerCurrent)
{
    int** NextRecurPointer = PointerCurrent + 1;
    if (NextRecurPointer == PointerEnd)
    {
        //print
        for (int* PrintPosition = *PointerCurrent; PrintPosition <= *PointerEnd; ++PrintPosition)
        {
            std::cout << *(PrintPosition) << " ";
        }
        std::cout << '\n';
    }
    else 
    {
        int RemainingPointerNumber = PointerEnd - PointerCurrent + 1;
        for (int* IterPosition = *PointerCurrent; IterPosition <= ArrayEnd - RemainingPointerNumber; ++IterPosition)
        {
            RecurPointer(ArrayStart, ArrayEnd, PointerStart, PointerEnd, PointerCurrent + 1);
        }
    }
    return;
}

int main(void)
{
    // Input
    int N, M; // ( 1 <= M <= N <= 8)
    std::cin >> N >> M;

    int* Array = new int[N];
    for (std::size_t i = 0; i < N; ++i)
    {
        Array[i] = i + 1;
    }

    int* const Ptr_ArrayStart = &Array[0];
    int* const Ptr_ArrayEnd = &Array[N - 1];

    // Process
    int** Pointers = new int*[M];
    for (std::size_t i = 0; i < M; ++i)
    {
        Pointers[i] = &Array[i];
    }
    // Output
    RecurPointer(Ptr_ArrayStart, Ptr_ArrayEnd, Pointers, &Pointers[M - 1], Pointers);
    return 0;
}

