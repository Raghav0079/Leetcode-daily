#include <string>
#include <vector>
#include <algorithm>
#include <bit>

struct Group {
    int start;
    int length;
};

class SparseTable {
public:
    SparseTable() = default;
    
    void build(const std::vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;

        int k = std::__lg(n) + 1;
        st.assign(k, std::vector<int>(n, 0));
        st[0] = nums;

        for (int i = 1; i < k; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = std::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r || n == 0) return 0;
        int i = std::__lg(r - l + 1);
        return std::max(st[i][l], st[i][r - (1 << i) + 1]);
    }

private:
    int n{0};
    std::vector<std::vector<int>> st;
};

class Solution {
public:
    std::vector<int> maxActiveSectionsAfterTrade(std::string s, std::vector<std::vector<int>>& queries) {
        int ones = 0;
        for (char c : s) {
            if (c == '1') ones++;
        }

        // 1. Group consecutive '0's and record group index for each string position
        auto [zeroGroups, zeroGroupIndex] = getZeroGroups(s);
        int numZeroGroups = zeroGroups.size();

        // 2. Compute adjacent pair merge lengths
        std::vector<int> zeroMergeLengths(std::max(0, numZeroGroups - 1));
        for (int i = 0; i + 1 < numZeroGroups; ++i) {
            zeroMergeLengths[i] = zeroGroups[i].length + zeroGroups[i + 1].length;
        }

        // 3. Build Sparse Table over merged zero lengths
        SparseTable st;
        st.build(zeroMergeLengths);

        std::vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];

            int left = (s[l] == '0' && zeroGroupIndex[l] != -1) 
                       ? (zeroGroups[zeroGroupIndex[l]].length - (l - zeroGroups[zeroGroupIndex[l]].start)) 
                       : -1;
            int right = (s[r] == '0' && zeroGroupIndex[r] != -1) 
                        ? (r - zeroGroups[zeroGroupIndex[r]].start + 1) 
                        : -1;

            int startAdjacentGroupIndex = zeroGroupIndex[l] + 1;
            int endAdjacentGroupIndex = (s[r] == '1' ? zeroGroupIndex[r] : zeroGroupIndex[r] - 1) - 1;

            int activeSections = ones;

            // Case 1: Substring strictly spans 2 adjacent zero groups trimmed at l and r
            if (s[l] == '0' && s[r] == '0' && zeroGroupIndex[l] + 1 == zeroGroupIndex[r]) {
                activeSections = std::max(activeSections, ones + left + right);
            } 
            // Case 2: Query fully enclosed adjacent zero-group pairs via Sparse Table
            else if (startAdjacentGroupIndex <= endAdjacentGroupIndex) {
                activeSections = std::max(activeSections, ones + st.query(startAdjacentGroupIndex, endAdjacentGroupIndex));
            }

            // Case 3: Partial left zero group + full adjacent zero group
            if (s[l] == '0' && zeroGroupIndex[l] + 1 <= (s[r] == '1' ? zeroGroupIndex[r] : zeroGroupIndex[r] - 1)) {
                activeSections = std::max(activeSections, ones + left + zeroGroups[zeroGroupIndex[l] + 1].length);
            }

            // Case 4: Partial right zero group + full preceding zero group
            if (s[r] == '0' && zeroGroupIndex[l] < zeroGroupIndex[r] - 1) {
                activeSections = std::max(activeSections, ones + right + zeroGroups[zeroGroupIndex[r] - 1].length);
            }

            ans.push_back(activeSections);
        }

        return ans;
    }

private:
    std::pair<std::vector<Group>, std::vector<int>> getZeroGroups(const std::string& s) {
        std::vector<Group> zeroGroups;
        std::vector<int> zeroGroupIndex(s.length(), -1);

        for (int i = 0; i < (int)s.length(); ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, 1});
                }
                zeroGroupIndex[i] = zeroGroups.size() - 1;
            } else {
                zeroGroupIndex[i] = zeroGroups.empty() ? -1 : (int)zeroGroups.size() - 1;
            }
        }
        return {zeroGroups, zeroGroupIndex};
    }
};