class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        
        vector<vector<int>> curSumX(m, vector<int>(n, 0));
        vector<vector<int>> curSumY(m, vector<int>(n, 0));

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                int x = (grid[i][j] == 'X') ? 1 : 0;
                int y = (grid[i][j] == 'Y') ? 1 : 0;

                
                curSumX[i][j] = x;
                curSumY[i][j] = y;

                if (i > 0) {
                    curSumX[i][j] += curSumX[i - 1][j];
                    curSumY[i][j] += curSumY[i - 1][j];
                }
                if (j > 0) {
                    curSumX[i][j] += curSumX[i][j - 1];
                    curSumY[i][j] += curSumY[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    curSumX[i][j] -= curSumX[i - 1][j - 1];
                    curSumY[i][j] -= curSumY[i - 1][j - 1];
                }

                
                if (curSumX[i][j] == curSumY[i][j] && curSumX[i][j] > 0) {
                    count++;
                }
            }
        }
        return count;
    }
};
