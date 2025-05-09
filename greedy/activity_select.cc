#include <algorithm>
#include <iostream>
#include <numeric>

static constexpr int N = 11;
int greedy_activity_selector(int s[], int f[], bool a[])
{
    a[0] = true;
    int count = 1, k = 0;
    for (int m = 1; m < N; ++m) {
        if (s[m] >= f[k]) {
            a[m] = true;
            k = m;
            ++count;
        } else {
            a[m] = false;
        }
    }
    return count;
}

int recursive_activity_selector(int s[], int f[], int k, bool a[])
{
    static int count = 0;
    int m = k + 1;
    while (m < N && s[m] < f[k]) {
        a[m] = false;
        m++;
    }

    if (m < N) {
        a[m] = true;
        count++;
        return recursive_activity_selector(s, f, m, a);
    } else {
        int res = count;
        count = 0;
        return res;
    }
}

// subproblem Sₖ: the set of activities that start after aₖ finishes (s)
// entire problem: recursive_activity_selector(s, f, -1)
int recursive_activity_selector(int s[], int f[], bool a[])
{
    return recursive_activity_selector(s, f, -1, a);
}

int main(int argc, char* argv[]) {
    int s[N] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[N] = {9, 13, 7, 6, 11, 4, 8, 11, 12, 5, 14};

    // template<class ForwardIt, class T>
    // std::iota(ForwardIt first, ForwardIt last, T value);

    // Fill the range with sequentially increasing value, starting with `value` 
    // and repetitively evaluating `++value` 
    int indices[N];
    std::iota(indices, indices + N, 0);

    std::sort(indices, indices + N, [&f](int i, int j) {
        return f[i] < f[j];  // Sort indices based on the values in f
    });


    int s_copy[N], f_copy[N];
    std::copy(s, s + N, s_copy);
    std::copy(f, f + N, f_copy);

    for (size_t i = 0; i < N; ++i) {
        s[i] = s_copy[indices[i]];
        f[i] = f_copy[indices[i]];
    }

    if (!std::is_sorted(f, f + N)) {
        std::cerr << "f[n] is not sorted" << std::endl;
        return 1;
    }


    std::cout << "Sorted s: ";
    for (const auto& value : s) std::cout << value << " ";
    std::cout << std::endl;

    std::cout << "Sorted f: ";
    for (const auto& value : f) std::cout << value << " ";
    std::cout << std::endl;


    bool activities[N] = {};
    std::cout << greedy_activity_selector(s, f, activities) << std::endl;
    std::cout << recursive_activity_selector(s, f, activities) << std::endl;

    return 0;
}

