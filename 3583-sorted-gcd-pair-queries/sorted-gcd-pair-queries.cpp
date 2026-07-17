#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());
        
        // Count frequencies of each number in nums
        vector<int> cnt(mx + 1, 0);
        for (int x : nums) {
            cnt[x]++;
        }
        
        // cntG[i] will store the number of pairs with GCD exactly equal to i
        vector<long long> cntG(mx + 1, 0);
        
        // Iterate backwards to compute exact GCD pair counts
        for (int i = mx; i > 0; --i) {
            long long v = 0;
            // Count how many elements are multiples of i
            for (int j = i; j <= mx; j += i) {
                v += cnt[j];
                cntG[i] -= cntG[j]; // Subtract pairs that have a larger multiple of i as GCD
            }
            cntG[i] += v * (v - 1) / 2; // Total pairs with a common divisor of at least i
        }
        
        // Build prefix sum of GCD pair counts
        for (int i = 1; i <= mx; ++i) {
            cntG[i] += cntG[i - 1];
        }
        
        // Answer each query using binary search (upper_bound)
        vector<int> ans;
        ans.reserve(queries.size());
        for (long long q : queries) {
            // Find the first GCD index where cumulative pairs count is strictly greater than q
            auto it = upper_bound(cntG.begin(), cntG.end(), q);
            ans.push_back(distance(cntG.begin(), it));
        }
        
        return ans;
    }
};