#include <cmath>

// for 1 ≤ i < j ≤ n, the i-th line intersects the j-th line iff π(i) > π(j)
//
// Example π(i) = {8,7,4,2,5,1,9,3,10,6}
//
// MNS: Maximum Non-crossing Subset

// c[1:n] π(i)

void mnset(int* c, const int n, int** size)
{
    for (int j = 0; j < c[1]; ++j)
        size[1][j] = 0;
    for (int j = c[1]; j <= n; ++j)
        size[1][j] = 1;

    for (int i = 2; i < n; ++i) {
        for (int j = 0; j < c[i]; ++j)
            size[i][j] = size[i - 1][j];
        for (int j = c[i]; j <= n; ++j)
            size[i][j] = std::max(size[i - 1][j], size[i - 1][c[i] - 1] + 1);

        size[n][n] = std::max(size[n - 1][n], size[n - 1][c[n] - 1] + 1);
    }
}

int mnset_traceback(int* c, const int n, int** size, int* net)
{
    int j = n;
    int m = 0;
    for (int i = n; i > 1; --i) {
        if (size[i][j] != size[i - 1][j]) {
            net[m++] = i;
            j = c[i] - 1;
        }
    }

    if (j >= c[1])
        net[m++] = 1;
    return m;
}
