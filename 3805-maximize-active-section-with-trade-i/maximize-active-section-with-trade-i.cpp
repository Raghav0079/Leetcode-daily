#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxActiveSectionsAfterTrade(std::string s) {
        int n = s.size();
        int totalOnes = 0;

        // Group consecutive characters into (char_type, length) pairs
        std::vector<std::pair<char, int>> groups;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int len = j - i;
            groups.push_back({s[i], len});
            if (s[i] == '1') {
                totalOnes += len;
            }
            i = j;
        }

        int maxGain = 0;

        // Look for patterns: '0' block (z1), '1' block (l1), '0' block (z2)
        for (size_t i = 1; i + 1 < groups.size(); ++i) {
            if (groups[i].first == '1') {
                int z1 = groups[i - 1].second; // Left block of '0's
                int z2 = groups[i + 1].second; // Right block of '0's

                // Net gain = z1 + z2
                maxGain = std::max(maxGain, z1 + z2);
            }
        }

        return totalOnes + maxGain;
    }
};