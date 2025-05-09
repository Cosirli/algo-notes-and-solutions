#include <iostream>
#include <vector>
#include "../divide-and-conquer/rng.h"

void bubblesort(std::vector<int>& arr, int n)
{
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            if (arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<int> arr;
    size_t array_size = 5000;
    arr.reserve(array_size);
    random_int_vec_gen(arr, array_size, 0, 1000);

    // quicksort(arr, 0, array_size - 1);
    bubblesort(arr, array_size);

    for (int it : arr) std::cout << it << " ";
    std::cout << std::endl;
    return 0;
}

