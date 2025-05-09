#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

// Time complexity: O(nc)
void knapsack_dp_basic(vector<int>& v, vector<int>& w, int c, vector<vector<int>>& m)
{
    int n = v.size() - 1;
    // j: capacity
    int j_max = min(w[n] - 1, c);
    for (int j = 0; j <= j_max; ++j)        // 0 <= j < min(w[i], c - 1)
        m[n][j] = 0;
    for (int j = j_max + 1; j <= c; ++j)    // w[i] <= j <= c
        m[n][j] = v[n];

    // loop i == 1 is unnecessary, since m[1][c] is determined by m[2][...]
    for (int i = n - 1; i > 1; --i) {
        j_max = min(w[n] - 1, c);
        for (int j = 0; j <= j_max; ++j)
            m[i][j] = m[i + 1][j];
        for (int j = j_max + 1; j <= c; ++j)
            m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);
    }

    if (w[1] > c)    // target: m[1][c]
        m[1][c] = m[2][c];
    else
        m[1][c] = max(m[2][c], m[2][c - w[1]] + v[1]);
}

double knapsack_jump(vector<int>& v, vector<int>& w, double c, vector<vector<int>>& p, int* head)
{
    int n = v.size() - 1;
    head[n + 1] = 0;       // meaning: head[x] means p[0:head[x]]?
    p[0][0] = 0;
    p[0][1] = 0;
    int left = 0, right = 0, next = 1;
    head[n] = 1;
    for (int i = n; i >= 1; --i) {
        int k = left;
        for (int j = left; j <= right; ++j) {
            double y = p[j][0] + w[i],
                   m = p[j][1] + v[i];
            if (y > c)    // capacity full
                break;
            while (k <= right && p[k][0] < y) {    // not dominated
                p[next][0] = p[k][0];
                p[next++][1] = p[k++][1];
            }

            if (k <= right && p[k][0] == y) {     // if y == p[k][0]
                if (m < p[k][1]) m = p[k][1];     // m = max(p[k][1], m);
                k++;
            }

            if (m > p[next - 1][1]) {
                p[next][0] = y;
                p[next++][1] = m;
            }

            while (k <= right && p[k][1] <= p[next - 1][1]) k++;
        }

        while (k <= right) {
            p[next][0] = p[k][0];
            p[next++][1] = p[k++][1];
        }
        left = right + 1;
        right = next - 1;
        head[i - 1] = next;
    }
    return p[next - 1][1];
}

void trace_knaps1(vector<vector<int>>& m, vector<int>& w, int c, vector<bool>& x)
{
    int n = w.size() - 1;
    for (int i = 1; i < n; ++i) {
        if (m[i][c] == m[i + 1][c]) {
            x[i] = 0;
        } else {
            x[i] = 1;
            c -= w[i];
        }
    }
}
