#include <vector>
#include <iostream>

// S(A,i,s)
class SubsetSum {
private:
    static std::vector<bool> x;
    static int n;
    static int sum;
    static int cnt;
    static bool found;

    static bool rec(std::vector<int>& arr, int i, int s,
                    std::vector<std::vector<int>>& memo)
    {
        if (s == 0)
            return true;
        if (i == 0)
            return arr[0] == s;
        if (memo)
        if (arr[i] > s)
            return rec(arr, i - 1, s);

        return rec(arr, i - 1, s - arr[i]) || rec(arr, i - 1, s);
    }

    // x[0:n-1]. choice: true or false
    // constraint:
    static void backtrack(std::vector<int>& arr, int t)
    {
        if (t > n - 1) return;

        for (int c = 0; c <= 1; ++c) {
            x[t] = c;
            if (c) cnt += arr[t];

            if (cnt == sum){
                found = true;
            } else if (cnt < sum) {
                backtrack(arr, t + 1);
            }

            if (c) cnt -= arr[t];
        }
    }

    static void init(std::vector<int>& arr, int sum)
    {
        SubsetSum::found = false;
        SubsetSum::n = arr.size();
        SubsetSum::sum = sum;
        SubsetSum::cnt = 0;
        SubsetSum::x.assign(n, false);
    }

public:
    static bool memoi_subset(std::vector<int>& arr, int sum)
    {
        init(arr, sum);
        using std::vector;
        vector<vector<int>> memoization(n, vector<int>(sum + 1, -1));
        return rec(arr, n - 1, sum, memoization);
    }

    static bool bt_subset(std::vector<int>& arr, int sum)
    {
        init(arr, sum);
        backtrack(arr, 0);
        return found;
    }

    static bool dp_subset_original(std::vector<int>& arr, int sum)
    {

    }
};

int SubsetSum::n;
int SubsetSum::sum;
int SubsetSum::cnt;
std::vector<bool> SubsetSum::x;
bool SubsetSum::found;

int main()
{
    std::vector<int> arr{3, 34, 4, 12, 5, 2};

    for (int i = 1; i <= 13; i += 2) {
        std::cout << SubsetSum::memoi_subset(arr, i) << std::endl;
        std::cout << SubsetSum::bt_subset(arr, i) << std::endl;
    }

    return 0;
}

