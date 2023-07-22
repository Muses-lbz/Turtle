//860. Lemonade Change
//At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy from you and order one at a time (in the order specified by bills). 
//Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill. 
//You must provide the correct change to each customer so that the net transaction is that the customer pays $5.
//Note that you do not have any change in hand at first.
//Given an integer array bills where bills[i] is the bill the ith customer pays, return true if you can provide every customer with the correct change, or false otherwise.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int fiveCount = 0;
        int tenCount = 0;

        for (int bill : bills) {
            if (bill == 5) {
                fiveCount++;
            }
            else if (bill == 10) {
                if (fiveCount >= 1) {
                    fiveCount--;
                    tenCount++;
                }
                else {
                    return false;
                }
            }
            else if (bill == 20) {
                if (tenCount >= 1 && fiveCount >= 1) {
                    tenCount--;
                    fiveCount--;
                }
                else if (fiveCount >= 3) {
                    fiveCount -= 3;
                }
                else {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution solution;
    vector<int> bills = { 5, 5, 5, 10, 20 };

    if (solution.lemonadeChange(bills)) {
        cout << "You can give correct change to every customer." << endl;
    }
    else {
        cout << "Sorry, you cannot give correct change to every customer." << endl;
    }

    return 0;
}
