//1499. Max Value of Equation
//You are given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, 
//where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.
//Return the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
//It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.

 //Example 1:
//Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
//Output: 4
//Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
//No other pairs satisfy the condition, so we return the max of 4 and 1.

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        deque<pair<int, int>> window; // 存储(xi - yi, xi)这样的pair
        int res = INT_MIN;

        for (const auto& point : points) {
            int x = point[0];
            int y = point[1];

            // 步骤 1：移除窗口外的点 (xi - xj > k)
            while (!window.empty() && x - window.front().second > k) {
                window.pop_front();
            }

            // 步骤 2：计算当前值 (yi + yj + |xi - xj|)
            if (!window.empty()) {
                int val = window.front().first + y + x;
                res = max(res, val);
            }

            // 步骤 3：移除窗口内比当前点更小的点 (yi - xi较小的点不可能成为最大值的候选)
            while (!window.empty() && y - x >= window.back().first) {
                window.pop_back();
            }

            // 将当前点加入窗口
            window.push_back({ y - x, x });
        }

        return res;
    }
};

int main() {
    vector<vector<int>> points = { {1, 3}, {2, 0}, {5, 10}, {6, -10} };
    int k = 1;

    Solution sol;
    int result = sol.findMaxValueOfEquation(points, k);

    cout << "最大值为: " << result << endl;

    return 0;
}
