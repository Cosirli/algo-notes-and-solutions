#include <algorithm>

#define MAX(a,b) ((((a) > (b)) ? (a) : (b)))

struct JobType {
    int key, index;
    bool job;    // true if a[i] <= b[i]

    bool operator<=(JobType& a) const
    {
        return key <= a.key;
    }
};

int flowshop(int* a, int* b, int* c, int n)
{
    JobType *d = new JobType[n];
    for (int i = 0; i < n; ++i) {
        d[i].key = (a[i] <= b[i]) ? a[i] : b[i];    // take the smaller as key
        d[i].job = a[i] <= b[i];
        d[i].index = i;
    }
    std::sort(d, d + n);

    int j = 0, k = n - 1;
    for (int i = 0; i < n; ++i) {
        if (d[i].job) {
            c[j++] = d[i].index;
        } else {
            c[k--] = d[i].index;
        }
    }

    j = a[c[0]];        // first a
    k = j + b[c[0]];    // first a + b
    for (int i = 1; i < n; ++i) {
        j += a[c[i]];
        k += MAX(j, k) + b[c[i]];
    }

    delete[] d;
    return k;
}
