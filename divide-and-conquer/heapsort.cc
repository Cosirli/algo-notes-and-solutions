#include <vector>
#include <iostream>
#include <algorithm>

class MaxHeap {
private:
    int left(int i) { return 2 * i; }

    int right(int i) { return 2 * i + 1; }

    void max_heapify_recs(int i, int n)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l <= n && heap_[l] > heap_[largest]) {
            largest = l;
        }
        if (r <= n && heap_[r] > heap_[largest]) {
            largest = r;
        }

        if (largest != i) {
            std::swap(heap_[i], heap_[largest]);
            max_heapify_recs(largest, n);
        }
    }

    void max_heapify_iter(int i, int n)
    {
        int curr = i;

        while (true) {
            int largest = curr;
            int l = left(curr);
            int r = right(curr);

            if (l <= n && heap_[l] > heap_[largest]) {
                largest = l;
            }
            if (r <= n && heap_[r] > heap_[largest]) {
                largest = r;
            }

            if (largest == curr) {
                break;
            }
            std::swap(heap_[curr], heap_[largest]);
            curr = largest;
        }
    }

    void build()
    {
        int n = heap_.size() - 1;
        for (int i = n / 2; i >= 1; --i) {
            max_heapify_iter(i, n);
        }
    }


public:
    MaxHeap(const std::vector<int>& arr)
    {
        int n = arr.size();
        heap_.reserve(n + 1);
        heap_.push_back(0);
        heap_.insert(heap_.end(), arr.begin(), arr.end());
    }

    void sort()
    {
        build();
        int n = heap_.size() - 1;
        int i;
        for (i = n; i >= 2; --i) {
            std::swap(heap_[1], heap_[i]);
            n--;
            max_heapify_iter(1, n);
        }
    }
    void print_vector()
    {
        int n = heap_.size() - 1;
        for (int i = 1; i <= n; ++i) {
            std::cout << heap_[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> heap_;

};

int main()
{
    MaxHeap heap({9, 3, 7, 1, 5, 6, 2, 5, 8, 4});

    heap.sort();

    heap.print_vector();


    return 0;
}
