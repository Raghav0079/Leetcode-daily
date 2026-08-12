#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            freq[nums[right]]++;
            
            // If the frequency of the current element exceeds k, 
            // shrink the window from the left until it's valid again.
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }
            
            // Update the maximum length of the valid window.
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};