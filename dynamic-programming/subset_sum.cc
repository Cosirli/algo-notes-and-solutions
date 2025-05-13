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
            return memo[0][s] = arr[0] == s;

        if (memo[i][s] != -1)
            return memo[i][s];

        if (arr[i] > s)
            return memo[i][s] = rec(arr, i - 1, s, memo);

        return memo[i][s] = (rec(arr, i - 1, s - arr[i], memo) || rec(arr, i - 1, s, memo));
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
        int n = arr.size();
        using std::vector;
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
        for (int i = 0; i <= n; ++i) dp[i][0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int s = 1; s <= sum; ++s) {
                if (arr[i - 1] > s)
                    dp[i][s] = dp[i - 1][s];
                else
                    dp[i][s] = dp[i - 1][s] || dp[i - 1][s - arr[i - 1]];
            }
        }
        return dp[n][sum];
    }

    static bool dp_subset_optimized(std::vector<int>& arr, int sum)
    {
        int n = arr.size();
        using std::vector;
        vector<bool> prev(sum + 1, false), curr(sum + 1, false);
        prev[0] = curr[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int s = 1; s <= sum; ++s) {
                if (arr[i - 1] > s)
                    curr[s] = prev[s];
                else
                    curr[s] = prev[s] || prev[s - arr[i - 1]];
            }
            prev = curr;    // overrite prev with curr
        }
        return prev[sum];
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
        std::cout << SubsetSum::bt_subset(arr, i) << std::endl;
        std::cout << SubsetSum::memoi_subset(arr, i) << std::endl;
        std::cout << SubsetSum::dp_subset_original(arr, i) << std::endl;
        std::cout << SubsetSum::dp_subset_optimized(arr, i) << std::endl;
    }

    return 0;
}

