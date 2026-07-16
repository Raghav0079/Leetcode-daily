#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixGcd(n);
        
        int mxi = 0;
        for (int i = 0; i < n; ++i) {
            mxi = max(mxi, nums[i]);
            prefixGcd[i] = std::gcd(nums[i], mxi);
        }
        
        sort(prefixGcd.begin(), prefixGcd.end());
        
        long long totalSum = 0;
        int left = 0;
        int right = n - 1;
        
        while (left < right) {
            totalSum += std::gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }
        
        return totalSum;
    }
};