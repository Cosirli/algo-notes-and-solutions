#include <vector>
#include <iostream>
#include "rng.h"

void merge1(std::vector<int>& arr, int p, int q, int r)
{
    std::vector<int> tmp(r - p + 1);
    int i = p, j = q + 1, k = 0;

    // Make the code more amenable to be translated into conditional moves
    while (i <= q && j <= r) {
        int v1 = arr[i], v2 = arr[j];
        int take1 = v1 < v2;
        tmp[k++] = take1 ? v1 : v2;
        i += take1;
        j += (1 - take1);
    }

    while (i <= q)
        tmp[k++] = arr[i++];

    while (j <= r)
        tmp[k++] = arr[j++];

    for (int i = 0; i < tmp.size(); ++i)
        arr[p + i] = tmp[i];
}

void merge2(std::vector<int>& arr, int p, int q, int r)
{
    int left_len = q - p + 1, right_len = r - q;
    std::vector<int> left(left_len);
    std::vector<int> right(right_len);

    for (int i = 0; i < left_len; ++i) 
        left[i] = arr[p + i];
    for (int j = 0; j < right_len; ++j) 
        right[j] = arr[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < left_len && j < right_len) {
        if (left[i] < right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }

    while (i < left_len)
        arr[k++] = left[i++];

    while (j < right_len)
        arr[k++] = right[j++];
}


void mergesort_helper(std::vector<int>& arr, int p, int r)
{
    if (p >= r) return;
    int q = p + (r - p) / 2;
    mergesort_helper(arr, p, q);
    mergesort_helper(arr, q + 1, r);
    // or use merge1(arr, p, q, r);
    merge2(arr, p, q, r);
}

void merge_sort(std::vector<int>& arr)
{
    mergesort_helper(arr, 0, arr.size() - 1);
}


void print_vector(const std::vector<int>& arr)
{
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // std::vector<int> arr = {9, 3, 7, 1, 5, 6, 2, 5, 8, 4};
    std::vector<int> arr;
    random_int_vec_gen(arr, 1000000, 0, 1000);
    
    std::cout << "Original array: ";
    print_vector(arr);

    // Perform merge sort
    merge_sort(arr);

    std::cout << "Sorted array: ";
    print_vector(arr);

    return 0;
}
