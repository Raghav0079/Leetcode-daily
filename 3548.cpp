class Solution {
public:
    typedef long long ll;
    ll totalSum = 0;

    bool checkHorCuts(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        ll topSum = 0;

        // Iterate through all possible horizontal cuts (leaving at least one row in each)
        for (int i = 0; i < m - 1; i++) {
            // Add current row to topSum
            for (int j = 0; j < n; j++) {
                topSum += grid[i][j];
            }

            ll bottomSum = totalSum - topSum;
            ll diff = topSum - bottomSum;

            // Case 1: Perfect split
            if (diff == 0) return true;

            // Case 2: Discount one cell from the heavier side
            if (diff > 0) {
                // Top is heavier: check if any cell in the TOP section equals 'diff'
                for (int r = 0; r <= i; r++) {
                    for (int c = 0; c < n; c++) {
                        if ((ll)grid[r][c] == diff) return true;
                    }
                }
            } else {
                // Bottom is heavier: check if any cell in the BOTTOM section equals abs(diff)
                ll target = -diff;
                for (int r = i + 1; r < m; r++) {
                    for (int c = 0; c < n; c++) {
                        if ((ll)grid[r][c] == target) return true;
                    }
                }
            }
        }
        return false;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        totalSum = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                totalSum += grid[i][j];
            }
        }

        // Check all horizontal cut possibilities
        if (checkHorCuts(grid)) return true;

        // Transpose the grid to check all vertical cut possibilities using the same logic
        vector<vector<int>> transposeGrid(n, vector<int>(m));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                transposeGrid[j][i] = grid[i][j];
            }
        }

        if (checkHorCuts(transposeGrid)) return true;

        return false;
    }
};
