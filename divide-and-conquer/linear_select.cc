#include <iostream>
#include <algorithm>
#include <sys/select.h>
#include <vector>
#include <random>
#include <ctime>
#include <stdexcept>

int hoare_partition(std::vector<int>& arr, int p, int r);
int randomized_partition(std::vector<int>& arr, int p, int r);
int partition_around(std::vector<int>& arr, int p, int r, int x);

// find the i-th order statistic in A[p:r] (the i-th smallest element)
int randomized_select(std::vector<int>& arr, int p, int r, int i)
{
    if (p == r)
        return arr[p];    // 1 <= i <= r - p + 1,  p == r => i == 1

    int q = randomized_partition(arr, p, r);
    int k = q - p + 1;    // the number of elements in A[p:q], including A[q]
    if (i == k) {
        return arr[q];
    } else if (i < k) {
        return randomized_select(arr, p, q - 1, i);
    } else {
        return randomized_select(arr, q + 1, r, i - k);
    }
}

// A[p:r]
int select(std::vector<int>& arr, int p, int r, int i)
{
    std::vector<int>::iterator it = arr.begin();
    if (r - p < 5) {    // you can change the '5' here to 75
        std::sort(it + p, it + r + 1);
        return arr[p + i - 1];
    }

    int n = r - p + 1;     // n >= 5
    int m = (n + 4) / 5;   // number of groups
    for (int g = 0; g < m; ++g) {
        int left = p + 5*g;
        int right = (left + 5 < r) ? (left + 5) : r;
        int median_index = left + (right - left) / 2;
        std::sort(it + left, it + right);
        std::swap(arr[p + g], arr[median_index]);
    }

    // recursively find the median of medians
    int median_rank = (m + 1) / 2;   // ceiling(m, 2);
    int x = select(arr, p, p + m - 1, n / 10);

    int q = partition_around(arr, p, r, x);
    int k = q - p + 1;
    if (i == k) {
        return arr[q];
    } else if (i < k) {
        return select(arr, p, q - 1, i);
    } else {
        return select(arr, q + 1, r, i - k);
    }
}


int hoare_partition(std::vector<int>& arr, int p, int r) {
    int i = p, j = r + 1, pivot = arr[p];
    for(;;) {
        while (arr[++i] < pivot && i != r);
        while (arr[--j] > pivot);
        if (i >= j)
            break;
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[j], arr[p]);
    return j;
}

int randomized_partition(std::vector<int>& arr, int p, int r)
{
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<int> dist(p, r);
    // int i = dist(gen);

    srand(time(NULL));
    int i = p + rand() % (r - p + 1);
    std::swap(arr[i], arr[p]);
    return hoare_partition(arr, p, r);
}


int partition_around(std::vector<int>& arr, int p, int r, int x)
{
    int index = -1;
    for (int i = p; i <= r; ++i) {
        if (arr[i] == x) {
            index = i;
            break;
        }
    }
    if (index == -1) throw std::runtime_error("Pivot not found");

    std::swap(arr[p], arr[index]);
    int i = p, j = r + 1, pivot = arr[p];
    for(;;) {
        while (arr[++i] < pivot && i != r);
        while (arr[--j] > pivot);
        if (i >= j)
            break;
        std::swap(arr[i], arr[j]);
    }
    std::swap(arr[j], arr[p]);
    return j;
}

int main()
{
    std::vector<int> arr = {12, 3, 5, 7, 4, 19, 26, 1, 8, 15};
    int n = arr.size();
    int rank = 5;    // expected element: 7
    if (rank < 1 || rank > n) {
        std::cerr << "Order statistic out of range\n";
        return 1;
    }
    int result = randomized_select(arr, 0, n - 1, rank);
    std::cout << "The " << rank << "-th smallest element is " << result << "\n";
    return 0;
}

