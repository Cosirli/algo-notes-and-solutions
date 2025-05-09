#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 编写一个算法，能够确定一个切割方案，使切割的总代价最小。
void MinCost(int L,int n,int *p){
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    sort(p + 1, p + n + 1);
    for (int len = 2; len <= n + 1; len++) {
        for (int i = 0; i <= n + 1 - len; i++) {
            int j = i + len;
            dp[i][j] = ~(1 << 31);
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + p[j] - p[i]);
            }
        }
    }
    cout << dp[0][n + 1];
}
//其中L是钢条长度，n是位置点个数，p包含n 个切割点的位置（乱序）

int main() {
    // 后台自动给出测试代码放在这里，无需同学编写
    int L, n;
    cin>>L>>n;
    int *p;
    p = new int[n+2];
    p[0] = 0;
    p[n+1] = L;
    for(int i=1;i<n+1;i++){
        cin>>p[i];
    }
    //调用函数输出一个切割最小的代价和，结果通过cout输出，均为int类型
    MinCost(L,n,p);
    return 0;
}
