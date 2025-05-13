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
void min_max(std::vector<int>& arr, int& min_val, int& max_val);

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
        int right = (left + 4 < r) ? (left + 4) : r;
        int median_index = left + (right - left) / 2;
        std::sort(it + left, it + right + 1);
        std::swap(arr[p + g], arr[median_index]);
    }

    // recursively find the median of medians
    int median_rank = (m + 1) / 2;   // ceiling(m, 2);
    int x = select(arr, p, p + m - 1, median_rank);

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

// let cnt be the number of comparisons necessary
// if n(arr.size()) is even, then cnt = 1 + 3(n-2)/2 = 3n/2 - 2
// if n is odd, cnt = 3(n-1)/2 = 3⌊n/2⌋
void min_max(std::vector<int>& arr, int& min_val, int& max_val)
{
    int n = arr.size();
    int i = 0, cmin, cmax, cmp;
    if (n == 0)
        throw std::invalid_argument("arr cannot be empty");

    if (n % 2 != 0) {
        cmin = cmax = arr[0];    // n is odd
        i = 1;
    } else {
        cmp = arr[i] < arr[i + 1];
        int imin = i + 1 - cmp, imax = i + cmp;
        cmin = arr[imin];
        cmax = arr[imax];
        i = 2;
    }

    for (; i <= n - 2; i += 2) {
        cmp = arr[i] < arr[i + 1];
        int imin = i + 1 - cmp, imax = i + cmp;
        cmin = (arr[imin] < cmin) ? arr[imin] : cmin;
        cmax = (arr[imax] > cmax) ? arr[imax] : cmax;
    }
    min_val = cmin;
    max_val = cmax;
}

int main()
{
    std::vector<int> arr = {12, 3, 5, 7, 4, 19, 26, 1, 8, 15};
    int n = arr.size();
    int rank = 5;    // expected element: 7
    if (rank < 1 || rank > n)
        throw std::out_of_range("Order statistic out of range");

    int result = select(arr, 0, n - 1, rank);
    std::cout << "The " << rank << "-th smallest element is " << result << "\n";

    std::cout << "\nMore tests ... \n";
    std::cout << "Please enter a rank in range [1,80]: ";
    std::vector<int> b {3,1,7,6,5,9,8,2,0,4,
               13,11,17,16,15,19,18,12,10,14,
               23,21,27,26,25,29,28,22,20,24,
               33,31,37,36,35,39,38,32,30,34,
               43,41,47,46,45,49,48,42,40,44,
               53,51,57,56,55,59,58,52,50,54,
               63,61,67,66,65,69,68,62,60,64,
               73,71,77,76,75,79,78,72,70,74,
              };    // [0,79]
    std::cin >> rank;
    result = select(b, 0, b.size() - 1, rank);
    std::cout << "The " << rank << "-th smallest element is " << result << "\n";
    return 0;
}
