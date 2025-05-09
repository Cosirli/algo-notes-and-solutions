#include <cmath>
#include <vector>
#include <algorithm>

#define MAX_VAL (~(1 << 31))

using namespace std;

// Optimal Binary Search Tree
// w: w(i,j) = Σp[k] (k belongs to p[i:j]) + Σq[k] (k belongs to q[i-1,j])
//
// e: expected search cost. for root r,
//      if (j == i - 1)
//        e[i,j] = q[i - 1]
//      else
//        e[i,j] = min{e[i, r - 1] + e[r + 1, j] + w(i,j)} (i ≦ r ≦ j)
//
// root[i][j]: best root for e[i,j]

// solution for BST[1:n] (p[1:n], q[0:n], root[1:n,1:n], e[1:n+1,0:n], w[1:n+1,0:n])
void optimal_BST(int n, vector<double>& p, vector<double>& q, vector<vector<int>>& root,
                 vector<vector<double>>& w, vector<vector<double>>& e)
{
    // base case when j == i - 1
    for (int i = 1; i <= n + 1; ++i) {
        w[i][i - 1] = q[i - 1];
        e[i][i - 1] = q[i - 1];
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            w[i][j] = w[i][j - 1] + p[i] + q[j];
            int curr_w = w[i][j];
            e[i][j] = MAX_VAL;
            for (int r = i; r <= j; ++r) {
                double tmp = e[i][r - 1] + e[r + 1][j] + curr_w;
                if (tmp < e[i][j]) {
                    e[i][j] = tmp;
                    root[i][j] = r;
                }
            }
        }
    }
}


