class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<int> st;

      
        vector<vector<int>> d1(m + 2, vector<int>(n + 2, 0));
        vector<vector<int>> d2(m + 2, vector<int>(n + 2, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                d1[i][j] = grid[i-1][j-1] + d1[i-1][j-1];
                d2[i][j] = grid[i-1][j-1] + d2[i-1][j+1];
                st.insert(grid[i-1][j-1]); 
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {

                for (int s = 1; ; s++) {
                    int top = i - s, bottom = i + s;
                    int left = j - s, right = j + s;


                    if (top < 1 || bottom > m || left < 1 || right > n) break;


                    int side1 = d1[i][right] - d1[top - 1][j - 1]; 
                    int side2 = d1[bottom][j] - d1[i - 1][left - 1]; 
                    int side3 = d2[i][left] - d2[top - 1][j + 1]; 
                    int side4 = d2[bottom][j] - d2[i - 1][right + 1]; 

                    int total = side1 + side2 + side3 + side4 
                                - grid[top-1][j-1] - grid[bottom-1][j-1] 
                                - grid[i-1][left-1] - grid[i-1][right-1];
                    
                    st.insert(total);
                }
            }
        }


        vector<int> res(st.rbegin(), st.rend());
        if (res.size() > 3) res.resize(3);
        return res;
    }
};
