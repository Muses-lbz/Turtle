//1388. Pizza With 3n Slices
//There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:
//You will pick any pizza slice.
//Your friend Alice will pick the next slice in the anti-clockwise direction of your pick.
//Your friend Bob will pick the next slice in the clockwise direction of your pick.
//Repeat until there are no more slices of pizzas.
//Given an integer array slices that represent the sizes of the pizza slices in a clockwise direction, return the maximum possible sum of slice sizes that you can pick.

//Example 1:
//Input: slices = [1,2,3,4,5,6]
//Output: 10
//Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. 
//Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        int k = n / 3;
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // 辅助函数：计算在一系列连续的披萨块中，选择不相邻的若干块所能得到的最大和
        auto calculateMaxSum = [&](int start, int end) {
            vector<int> slice(slices.begin() + start, slices.begin() + end);
            int m = slice.size();
            vector<vector<int>> dp(m + 1, vector<int>(k + 1, 0));

            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= k; ++j) {
                    // 选择当前披萨块或不选择，取较大值
                    dp[i][j] = max(dp[i - 1][j], (i >= 2 ? dp[i - 2][j - 1] : 0) + slice[i - 1]);
                }
            }

            return dp[m][k];
        };

        // 情况1：选择第一块披萨，不选择最后一块
        int maxSum1 = calculateMaxSum(0, n - 1);
        
        // 情况2：不选择第一块披萨，选择最后一块
        int maxSum2 = calculateMaxSum(1, n);

        // 返回两种情况下的较大值作为最终答案
        return max(maxSum1, maxSum2);
    }
};

int main() {
    Solution solution;
    vector<int> slices = {1, 2, 3, 4, 5, 6};
    cout << solution.maxSizeSlices(slices) << endl;
    return 0;
}
