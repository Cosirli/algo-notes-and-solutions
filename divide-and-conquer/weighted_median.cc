#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Swap two vectors simultaneously */
template< class T1, class T2 >
static void simul_swap(vector<T1>& arr1, vector<T2>& arr2, int i, int j);

static int simul_partition_around(vector<int>& arr, vector<double>& company, int p, int r, int value)
{
    int index;
    for (int i = p; i <= r; ++i) {
        if (arr[i] == value) {
            index = i;
            break;
        }
    }
    simul_swap(arr, company, r, index);
    int i = p - 1, j = r, pivot = value;
    for (;;) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot && j != p);
        if (i >= j)
            break;
        simul_swap(arr, company, i, j);
    }
    simul_swap(arr, company, i, r);
    return i;
}

static int simul_select(vector<int>& arr, vector<double>& company, int p, int r, int rank)
{
    if (p == r) return arr[p];

    int n = r - p + 1;
    int m = (n + 4) / 5;
    for (int g = 0; g < m; ++g) {
        int L = p + 5*g;
        int R = (L + 4 < r) ? (L + 4) : r;
        int M = L + (R - L) / 2;
        std::sort(arr.begin() + L, arr.begin() + R + 1);
        std::sort(company.begin() + L, company.begin() + R + 1, [&arr](int i, int j) {
            return arr[i] < arr[j];
        });
        simul_swap(arr, company, p + g, M);
    }

    int median_of_median = simul_select(arr, company, p, p + m - 1, (m + 1) / 2);
    int q = simul_partition_around(arr, company, p, r, median_of_median);
    int k = q - p + 1;
    if (rank == k) {
        return arr[q];
    } else if (rank < k) {
        return simul_select(arr, company, p, q, rank);
    } else {
        return simul_select(arr, company, q + 1, r, rank - k);
    }
}

void weighted_median(int length, vector<int> num, vector<double> weight, int p, int r)
{
    if (length == 1) {
        cout << num[p];
        return;
    }

    int mid = (length + 1) / 2;
    int v = simul_select(num, weight, p, r, mid);
    int q = simul_partition_around(num, weight, 0, length - 1, v);

    double wl = 0.0, wr = 0.0;
    for (int i = 0; i < q; ++i) wl += weight[i];
    for (int i = q + 1; i < length; ++i) wr += weight[i];

    if (wl <= 0.5 && wr <= 0.5) {
        cout << num[q];
        return;
    } else if (wl < 0.5 && wr > 0.5) {
        weighted_median(length, num, weight, q + 1, r);
    } else {
        weighted_median(length, num, weight, p, q - 1);
    }
}

void WeightMedian(int length, vector<int> num, vector<double> weight, int index)
{
    weighted_median(length, num, weight, index, length - 1);
    /*    A correct implementation of WeightMedian:
    int p = index, r = length - 1, mid = (length + 1) / 2;
    if (p == r) {
        cout << num[p];
        return;
    }

    int v = select(num, weight, p, r, mid);
    int q = partition_around(num, weight, p, r, v);

    double wl = 0.0, wr = 0.0;
    for (int i = p; i < q; ++i) wl += weight[i];
    for (int i = q + 1; i <= r; ++i) wr += weight[i];

    if (wl <= 0.5 && wr <= 0.5) {
        cout << num[q];
        return;
    } else if (wl < 0.5 && wr > 0.5) {
        WeightMedian(length, num, weight, q + 1);
    } else {
        WeightMedian(length, num, weight, 0);
    }
    */
}

int main() {
    //调用WeightMedian(length, num, weight,index) 函数，函数内部使用cout输出得到的中位数，测试代码默认index初始值为0
    //length为输入长度，num是包含n个互不相同元素值的向量，weight是包含元素值对应的权重的向量，index为递归调用时的索引(下标)
    vector<int> num;
    vector<double> weight;
    int length;
    cin >> length;
    for (int i = 0; i < length; i++) {
        int input;
        cin >> input;
        num.push_back(input);
    }
    for (int i = 0; i < length; i++) {
        double input;
        cin >> input;
        weight.push_back(input);
    }
    WeightMedian(length, num, weight, 0);
    return 0;
}

template< class T1, class T2 >
static void simul_swap(vector<T1>& arr1, vector<T2>& arr2, int i, int j)
{
    std::swap(arr1[i], arr1[j]);
    std::swap(arr2[i], arr2[j]);
}

/* A buggy implementation */
static void helper(int length, vector<int> num, vector<double> weight, double sl, double sr)
{
    if (length == 1) {
        cout << num[0];
        return;
    }
    vector<int> tmp(length);
    for (int i = 0; i < length; ++i)
        tmp[i] = num[i];
    int k = num[0];
    double wl = 0.0, wr = 0.0;
    for (int i = 0; i < length; ++i) {
        if (num[i] < k)
            wl += weight[i];
        else if (num[i] > k)
            wr += weight[i];
    }
    if (wl <= sl && wr <= sr) {
        cout << k;
        return;
    }

    vector<int> subk;
    vector<double> subw;
    if (wl > sl) {
        sr -= wr;
        for (int i = 0; i < length; ++i) {
            if (num[i] < k) {
                subk.push_back(num[i]);
                subw.push_back(weight[i]);
            }
        }
    } else {
        sl -= wl;
        for (int i = 0; i < length; ++i) {
            if (num[i] > k) {
                subk.push_back(num[i]);
                subw.push_back(weight[i]);
            }
        }
    }
    helper((int)subk.size(), subk, subw, sl, sr);
}
