#include <vector>
#include <iostream>
#include <cmath>

namespace NQueens {
    static std::vector<int> x;     // x[i] == j: this queen's position is (i,j)
    static int n;
    static unsigned long long sum = 0;
    static void solve(int n);
    static bool legal(int k);
    static void backtrack(int t);
}

static bool NQueens::legal(int k)
{
    for (int j = 1; j < k; ++j)
        if ((x[j] == x[k]) || (abs(j - k) == abs(x[j] - x[k])))
            return false;
    return true;
}

static void NQueens::backtrack(int t)
{
    if (t > n) {
        sum++;
        return;
    }

    for (int i = 1; i <= n; ++i) {
        x[t] = i;
        if (legal(t))
            backtrack(t + 1);
    }
}

static void NQueens::solve(const int num)
{
    sum = 0;
    n = num;
    x.assign(num + 1, 0);    // change x's size() and refresh its contents
    std::cout << "x.size(): "     << x.size()     << std::endl;
    std::cout << "x.capacity(): " << x.capacity() << std::endl;
    backtrack(1);
    std::cout << "Solution for " <<
        num << " queens problem: " << sum << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Please enter the number of queens" << std::endl;
        exit(1);
    }

    int board_size = atoi(argv[1]);
    NQueens::solve(8);
    NQueens::solve(board_size);
    return 0;
}


