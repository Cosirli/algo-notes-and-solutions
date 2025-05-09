#include "rng.h"
#include "insertion_sort.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

// Loop invariant: before each comparison of i and j,
// A[p:r] ==>
//            A[p:i-1]   elem <= pivot
//            A[i:j]     unsorted
//            A[j+1:r]   elem >= pivot
//            A[r]       elem == pivot
//
// when i < j, before swapping A[i] and A[j]:
//     A[i] >= pivot;
//     if j == p, then j <= i, contradicts;
//     so A[j] <= pivot
//
// when i >= j
//            If j == p, pivot is the smallest, swap(A[i], A[r]) is needed
//            If i == j, i is the pivot position. Break. Swap if you'd like to
//            If i > j, A[j] < pivot && A[i] > pivot, break and swap is needed
int hoare_partition(std::vector<int>& arr, int p, int r) {
    int pivot = arr[r];
    int i = p - 1, j = r;
    // std::cout << "\np: " << p << "  r: " << r << "  pivot: " << pivot << std::endl;
    for (;;) {
        while (arr[++i] < pivot);
        // in case pivot is the min elem
        while (arr[--j] > pivot) if (j == p) break;

        if (i >= j) {
            break;
        }
        std::swap(arr[i], arr[j]);
        // std::cout << "  swap " << i << " and " << j << std::endl;
        // for (int it : arr) std::cout << it << " "; std::cout << std::endl;
    }
    if (j == p || i > j) std::swap(arr[i], arr[r]);
    return i;   // vital decision
}

int lomuto_partition(std::vector<int>& arr, int p, int r)
{
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; ++j) {
        if (arr[j] <= x) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[r]);
    return i + 1;
}

int randomized_partition(std::vector<int>& arr, int p, int r)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(p, r);
    int i = dist(gen);

    std::swap(arr[i], arr[r]);
    return hoare_partition(arr, p, r);
}

int median_of_three_partition(std::vector<int>& arr, int p, int r)
{
    int mid = p + ((r - p) >> 1);
    if (arr[p] > arr[mid]) std::swap(arr[p], arr[mid]);
    if (arr[p] > arr[r]) std::swap(arr[p], arr[r]);
    if (arr[mid] > arr[r]) std::swap(arr[r], arr[mid]);

    std::swap(arr[mid], arr[r]);
    return hoare_partition(arr, p, r);
}

void quicksort(std::vector<int>& arr, int p, int r) {
    if (p >= r) return;

    int q = hoare_partition(arr, p, r); // pivot

    quicksort(arr, p, q - 1);
    quicksort(arr, q + 1, r);
}

void sort(std::vector<int>& arr, int p, int r) {
    if (r - p <= 16) {
        insertion_sort(arr, p, r);
        return;
    }

    int q = median_of_three_partition(arr, p, r);
    
    sort(arr, p, q - 1);
    sort(arr, q + 1, r);
}

int main(int argc, char* argv[]) {
    std::vector<int> arr;
    size_t array_size = 50;
    arr.reserve(array_size);
    random_int_vec_gen(arr, array_size, 0, 100);

    quicksort(arr, 0, array_size - 1);
    // sort(arr, 0, array_size - 1);

    for (int it : arr) std::cout << it << " ";
    std::cout << std::endl;
    return 0;
}
