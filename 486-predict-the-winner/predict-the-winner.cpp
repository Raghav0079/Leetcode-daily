#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        // dp[i] will store the maximum net score a player can get from a subarray starting at index i
        vector<int> dp = nums; 
        
        // Build the table from smaller subarrays to the full array
        for (int diff = 1; diff < n; diff++) {
            for (int i = 0; i < n - diff; i++) {
                int j = i + diff;
                dp[i] = max(nums[i] - dp[i + 1], nums[j] - dp[i]);
            }
        }
        
        // If Player 1's net score advantage is >= 0, Player 1 wins
        return dp[0] >= 0;
    }
};