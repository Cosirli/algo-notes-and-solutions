#include <iostream>

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    int a[]{3, 2, 9, 12, 1, 2, 4};
    insertion_sort(a, sizeof(a) / sizeof(a[0]));
    for (int item : a) {
        std::cout << item << std::endl;
    }
}
