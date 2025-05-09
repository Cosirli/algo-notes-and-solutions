#pragma once

#include <vector>

inline void insertion_sort(std::vector<int>& arr, int p, int r)
{
    for (int i = p + 1; i <= r; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= p && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

