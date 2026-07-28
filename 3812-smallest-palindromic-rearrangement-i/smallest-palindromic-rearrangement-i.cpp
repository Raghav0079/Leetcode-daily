#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string half = "";
        string mid = "";

        for (int i = 0; i < 26; ++i) {
            int half_count = count[i] / 2;
            half.append(half_count, 'a' + i);
            
            if (count[i] % 2 != 0) {
                mid = string(1, 'a' + i);
            }
        }

        string rev_half = half;
        reverse(rev_half.begin(), rev_half.end());

        return half + mid + rev_half;
    }
};