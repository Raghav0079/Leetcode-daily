class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        int startRow = x;
        int endRow = x + k - 1;

        int startCol = y;
        int endCol = y + k - 1; 


        for (int i = 0; i < k / 2; i++) {

            for (int j = startCol; j <= endCol; j++) {
                swap(grid[startRow + i][j], grid[endRow - i][j]);
            }
        }

        return grid;
    }
};
