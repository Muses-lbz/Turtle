// 1444. Number of Ways of Cutting a Pizza
//Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. 
//You have to cut the pizza into k pieces using k-1 cuts. 
//For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. 
//If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. 
//Give the last piece of pizza to the last person.
//Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        const int MOD = 1000000007;
        int rows = pizza.size();
        int cols = pizza[0].size();
        
        vector<vector<int>> prefixSum(rows + 1, vector<int>(cols + 1, 0));
        
        // 计算前缀和数组，用于快速计算矩形内包含的苹果数量
        for (int i = rows - 1; i >= 0; --i) {
            for (int j = cols - 1; j >= 0; --j) {
                prefixSum[i][j] = prefixSum[i + 1][j] + prefixSum[i][j + 1] - prefixSum[i + 1][j + 1] + (pizza[i][j] == 'A');
            }
        }
        
        auto hasApple = [&](int x1, int y1, int x2, int y2) {
            return prefixSum[x1][y1] - prefixSum[x2][y1] - prefixSum[x1][y2] + prefixSum[x2][y2] > 0;
        };
        
        vector<vector<vector<int>>> memo(rows, vector<vector<int>>(cols, vector<int>(k, -1)));
        
        function<int(int, int, int)> dp = [&](int x, int y, int slices) {
            // 若当前矩形不含苹果，则无法切割，返回0
            if (!hasApple(x, y, rows, cols)) {
                return 0;
            }
            // 若已切割k-1次，返回1
            if (slices == 0) {
                return 1;
            }
            // 若已经计算过当前状态，直接返回结果
            if (memo[x][y][slices] != -1) {
                return memo[x][y][slices];
            }
            
            int ways = 0;
            // 在垂直方向切割
            for (int i = x + 1; i < rows; ++i) {
                if (hasApple(x, y, i, cols)) {
                    ways = (ways + dp(i, y, slices - 1)) % MOD;
                }
            }
            // 在水平方向切割
            for (int j = y + 1; j < cols; ++j) {
                if (hasApple(x, y, rows, j)) {
                    ways = (ways + dp(x, j, slices - 1)) % MOD;
                }
            }
            
            memo[x][y][slices] = ways;
            return ways;
        };
        
        return dp(0, 0, k - 1);
    }
};

int main() {
    Solution solution;
    
    vector<string> pizza = {"A..","AAA","..."};
    int k = 3;
    
    cout << solution.ways(pizza, k) << endl;
    
    return 0;
}
