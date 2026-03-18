class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) { // Fixed: j++ and j < n
                
                // Add the value from the top
                if (i > 0) 
                    grid[i][j] += grid[i-1][j];
                
                // Add the value from the left
                if (j > 0) 
                    grid[i][j] += grid[i][j-1];
                
                // Subtract the top-left diagonal (it was added twice)
                if (i > 0 && j > 0) 
                    grid[i][j] -= grid[i-1][j-1];

                // If the sum of submatrix starting at (0,0) is <= k
                if (grid[i][j] <= k) {
                    count++;
                } else {
                    // Since elements are non-negative, if we exceed k, 
                    // further elements in this row will also exceed k.
                    break; 
                }
            }
        }
        return count;
    }
};
