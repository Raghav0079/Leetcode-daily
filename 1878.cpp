#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        set<int> st;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {

                st.insert(grid[r][c]);


                for (int s = 1; r - s >= 0 && r + s < m && c - s >= 0 && c + s < n; s++) {
                    int sum = 0;
                    
 
                    for (int i = 0; i < s; i++) {
                        sum += grid[r - s + i][c + i]; // Top to Right
                        sum += grid[r + i][c + s - i]; // Right to Bottom
                        sum += grid[r + s - i][c - i]; // Bottom to Left
                        sum += grid[r - i][c - s + i]; // Left to Top
                    }
                    st.insert(sum);
                }


                while (st.size() > 3) {
                    st.erase(st.begin());
                }
            }
        }


        vector<int> result(st.rbegin(), st.rend());
        return result;
    }
};
