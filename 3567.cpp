#include <vector>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size(); 

        
        vector<vector<int>> result(m - k + 1, vector<int>(n - k + 1));

        for (int i = 0; i <= m - k; i++) {
            for (int j = 0; j <= n - k; j++) {
                set<int> val;

                
                for (int r = i; r < i + k; r++) {
                    for (int c = j; c < j + k; c++) {
                        val.insert(grid[r][c]);
                    }
                }

                
                if (val.size() <= 1) {
                    result[i][j] = 0;
                    continue;
                }

                int minDiff = INT_MAX;
                auto it = val.begin();
                int prevVal = *it;
                it++;

       
                while (it != val.end()) {
                    minDiff = min(minDiff, *it - prevVal);
                    prevVal = *it;
                    it++;
                }

                result[i][j] = minDiff;
            }
        }
        return result;
    }
};
