class Solution {
public:
    int maximumLengthSubstring(string s) {
        int ans = 0;
        vector<int> count(26, 0);
        
        for (int l = 0, r = 0; r < s.length(); ++r) {
            ++count[s[r] - 'a'];
            
            // If any character exceeds 2 occurrences, shrink the window from the left
            while (count[s[r] - 'a'] > 2) {
                --count[s[l] - 'a'];
                ++l;
            }
            
            // Update the maximum length found so far
            ans = max(ans, r - l + 1);
        }
        
        return ans;
    }
};