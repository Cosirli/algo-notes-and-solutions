#include <iostream>
#include <string>
#include <vector>
using namespace std;

int lcs_length(string& x, string& y, int** b)
{
    int m = x.length() - 1;
    int n = y.length() - 1;
    vector<vector<int>> c(m + 1);

    for (int i = 0; i <= m; ++i) c[i][0] = 0;
    for (int i = 0; i <= n; ++i) c[0][i] = 0;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (x[i] == y[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }
    }

    return c[m][n];
}

void lcs_sequence(int i, int j, string& x, int** b)
{
    if (i == 0 || j == 0) return;

    if (b[i][j] == 1) {
        lcs_sequence(i - 1, j - 1, x, b);
        std::cout << x[i];
    } else if (b[i][j] == 2) {
        lcs_sequence(i - 1, j, x, b);
    } else {
        lcs_sequence(i, j - 1, x, b);
    }
}
